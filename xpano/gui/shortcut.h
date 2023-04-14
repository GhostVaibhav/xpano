#include "xpano/gui/action.h"

namespace xpano::gui {

enum class ShortcutType { kOpen, kExport, kDebug, kReset };

const char* Label(ShortcutType type);

Action CheckKeybindings();

}  // namespace xpano::gui
