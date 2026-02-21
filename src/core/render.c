#include <raygui.h>
#include "include/ui.h"

typedef enum {
    DISPLAY_NONE = 0,
    DISPLAY_LAYOUT_UPDATED = 1 << 0,
/*     DISPLAY_STATE_ = 1 << 2 */
} Display_Flags;


#define ELEMENT_STR(e) (char*)e.content.text.content.str

void DISPLAY_RenderElement(UI_element e){
  switch (e.type) {
  case UI_ELEMENT_NONE:
    break;
  case UI_ELEMENT_BUTTON:
    if(GuiButton(e.rect, ELEMENT_STR(e))){
      e.onClick_left();
    }
    break;
  case UI_ELEMENT_TEXTBOX:
    GuiTextBox(e.rect, ELEMENT_STR(e), e.content.text.content.size, false);
    break;
  case UI_ELEMENT_ICON:
    break;
  }
}

void DISPLAY_RenderUI(UI_element r){
  DISPLAY_RenderElement(r);

  if(r.content.children) DISPLAY_RenderUI(*r.content.children);
  if(r.next) DISPLAY_RenderUI(*r.next);
}

// single frame displaying of a ui tree
void DISPLAY_Root( UI_root* r, u32 display_state){
  if (BIT_FLAG_CMP(display_state, DISPLAY_LAYOUT_UPDATED)) {
    UI_UpdateLayout(r->root);
    BIT_FLAG_DELETE(display_state, DISPLAY_LAYOUT_UPDATED);
  }
  DISPLAY_RenderUI(*(r->root));
}
