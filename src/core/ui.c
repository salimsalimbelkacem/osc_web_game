// implement UI here

#include "include/ui.h"

static inline UI_element* UI_Alloc(arena* a) {
  return (UI_element*) ARENA_Alloc( a, sizeof(UI_element));
}

UI_root UI_Init(){
  arena a = ARENA_Init();
  UI_element* r = UI_InitElement((vec2){0, 0}, &a);

  r->area.width = SCREEN_WIDTH;
  r->area.height = SCREEN_HEIGHT;

  return (UI_root) {a, r};
}

UI_element* UI_InitElement( vec2 coord, arena* a){
  UI_element* e = UI_Alloc(a);

  e->area.x = coord.x;
  e->area.y = coord.y;
  e->area.width = 0;
  e->area.height = 0;

  e->onClick_left = NULL;
  e->onClick_right = NULL;
  e->onClick_middle = NULL;
  e->onHover = NULL;
  e->next = NULL;

  e->state = UI_STATE_NONE;

  e->layer = 0;  

  e->bg = (struct UI_Background) {.type = UI_BG_NONE, .alpha = 255};

  e->border = (struct UI_Border) {.type = UI_BG_NONE, .alpha = 255, .width=0};

  e->content = (struct UI_Content) {
    .type = UI_CONTENT_NONE,
    .h_align = UI_CONTENT_ALIGN_LEFT,
    .v_align = UI_CONTENT_ALIGN_MIDDLE,
    .padding = 0,
    .children_gap = 0,
    .stack_content = false,
  };

  return e;  
}


void UI_AppendElement(UI_element* e, UI_element* new_e){}
void UI_PopElement(UI_element* e, UI_element* new_e){}
void UI_AppendChild(UI_element* parent){}
void UI_PopChild(UI_element* parent){}


UI_element* UI_Button(string text){}
UI_element* UI_Textbox(string text){}
UI_element* UI_Icon(struct Image icon){}
UI_element* UI_InputBox(string placeholder){}
