#include "utils/text.h"

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <spdlog/spdlog.h>

#include "utils/resource.h"

namespace xpano::utils {

namespace {

std::optional<Text> LoadText(const std::filesystem::path& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    spdlog::error("Failed to open file {}", path.string());
    return {};
  }

  Text text = {path.filename().string(), {}};
  for (std::string line; std::getline(file, line);) {
    text.lines.push_back(line);
  }
  return text;
}

}  // namespace

std::vector<Text> LoadTexts(const std::string& executable_path,
                            const std::string& rel_path) {
  auto license_dir = resource::Find(executable_path, rel_path);
  if (!license_dir) {
    return {};
  }

  std::vector<Text> texts;
  for (const auto& file : std::filesystem::directory_iterator(*license_dir)) {
    if (auto text = LoadText(file.path()); text) {
      texts.emplace_back(std::move(*text));
    }
  }
  return texts;
}

}  // namespace xpano::utils