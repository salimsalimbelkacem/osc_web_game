#include <raygui.h>
#include <raylib.h>
#include "ui.h"

typedef enum {
    DISPLAY_NONE = 0,
    DISPLAY_LAYOUT_UPDATED = 1 << 0,
/*     DISPLAY_STATE_ = 1 << 2 */
} Display_Flags;
void DISPLAY_RenderElement(UI_element e);
void DISPLAY_RenderUI(UI_element r);
void DISPLAY_Root( UI_root* r, u32 display_state);
