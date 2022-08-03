#include "gui/layout.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace xpano::gui {

namespace {
void InitDockSpace(ImGuiID dockspace_id) {
  ImGuiID dock_main_id = dockspace_id;
  ImGuiID dock_id_thumbnails = ImGui::DockBuilderSplitNode(
      dock_main_id, ImGuiDir_Down, 0.20f, nullptr, &dock_main_id);
  ImGuiID dock_id_sidebar = ImGui::DockBuilderSplitNode(
      dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
  ImGuiID dock_id_logger = ImGui::DockBuilderSplitNode(
      dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);

  ImGui::DockBuilderDockWindow("PanoSweep", dock_id_sidebar);
  ImGui::DockBuilderDockWindow("Preview", dock_main_id);
  ImGui::DockBuilderDockWindow("Logger", dock_id_logger);
  ImGui::DockBuilderDockWindow("Images", dock_id_thumbnails);
  ImGui::DockBuilderFinish(dockspace_id);
}
}  // namespace

void Layout::Begin() {
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoNavFocus;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpaceWindow", nullptr, window_flags);
  ImGui::PopStyleVar(3);

  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  bool init_dockspace = ImGui::DockBuilderGetNode(dockspace_id) == nullptr;
  dockspace_id = ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),
                                  ImGuiDockNodeFlags_NoTabBar);
  ImGui::End();

  if (init_dockspace) {
    InitDockSpace(dockspace_id);
  }
}

void Layout::ToggleLogger() { show_logger_ = !show_logger_; }

bool Layout::ShowLogger() const { return show_logger_; }

}  // namespace xpano::gui