// implement UI here

#include "include/ui.h"
#include <raylib.h>

static inline UI_element* UI_Alloc(arena* a) {
  return (UI_element*) ARENA_Alloc( a, sizeof(UI_element));
}

static inline UI_element* UI_ListGetTail(UI_element* e) {
  if(!e) return NULL;

  UI_element* p = e;
  for(; p->next != NULL; p=p->next){}

  return p;
}

UI_root UI_Init(arena* a){
  UI_element* r = UI_InitElement(a);

  r->rect.width = SCREEN_WIDTH;
  r->rect.height = SCREEN_HEIGHT;

  r->id = STR("root");

  return (UI_root) {a, r};
}

UI_element* UI_InitElement( arena* a){
  UI_element* e = UI_Alloc(a);
  e->id = STR(NULL);

  e->rect.x = 0;
  e->rect.y = 0;
  e->rect.width = 0;
  e->rect.height = 0;
  e->gap = 0;
  e->content.text.font_size = 12;

  e->onClick_left = NULL;
  e->onClick_right = NULL;
  e->onClick_middle = NULL;
  e->onHover = NULL;
  e->next = NULL;
  e->prev = NULL;
  e->parent = NULL;

  e->type = UI_ELEMENT_NONE;

  /* e->state = UI_STATE_NONE; */

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
    .text.font_size = UI_DEF_TXT_FONT_SIZE,
  };

  return e;  
}

void inline UI_AppendElement(UI_element *e, UI_element *new_e) {
  UI_element *tail = UI_ListGetTail(e);

  tail->next = new_e;
  new_e->prev = tail;
  new_e->next = NULL;
}

void UI_AppendChild(UI_element* parent, UI_element* new_e){

  new_e->layer = parent->layer;
  new_e->gap = parent->content.children_gap;

  if (parent->content.children == NULL) {
    parent->content.children = new_e;
    new_e->parent = parent;
    new_e->next = NULL;

    return;    
  }

  UI_AppendElement( parent->content.children, new_e);
  new_e->next = NULL;
}

/* void UI_PopChild(UI_element* parent){} */
/* void UI_PopElement(UI_element* e, UI_element* new_e){} */


UI_element* UI_TextButton(arena* a, string text, UI_Action onclick){
  UI_element* butt = UI_InitElement(a);
  butt->type = UI_ELEMENT_BUTTON;

  butt->content.type = UI_CONTENT_TEXT;  
  butt->content.text.content = ARENA_strcpy(a, text);

  return butt;  
}

UI_element* UI_IconButton(arena* a, struct Image icon){
  UI_element* butt = UI_InitElement(a);
  butt->type = UI_ELEMENT_BUTTON;

  butt->content.type = UI_CONTENT_IMAGE;  
  butt->content.icon = icon;
  
  return butt;
}

UI_element* UI_Textbox(arena* a, string text){
  UI_element* text_box = UI_InitElement(a);
  text_box->type = UI_ELEMENT_TEXTBOX;
  
  text_box->content.type = UI_CONTENT_TEXT;  
  text_box->content.text.content = ARENA_strcpy(a, text);

  return text_box;  
}

UI_element *UI_Heading(arena *a, string text, u8 level) {
  UI_element* heading = UI_InitElement(a);

  heading->content.type = UI_CONTENT_TEXT;
  heading->content.text.content = ARENA_strcpy(a, text);

  switch (level) {
  case 1:
    heading->content.text.font_size = UI_DEF_H1_FONT_SIZE;
    break;
  case 2:
    heading->content.text.font_size = UI_DEF_H2_FONT_SIZE;
    break;
  case 3:
    heading->content.text.font_size = UI_DEF_H3_FONT_SIZE;
    break;
  }

  return heading;  
}

void __UI_UpdateLayout__(UI_element* r, bool stacking){
  // this is not ai generated it's just that the code is confusing

  UI_element* ptr = r;

  // set pos
  if (ptr->parent) { // checks if it's the first child
    ptr->rect.x = ptr->parent->rect.x + ptr->parent->content.padding;
    ptr->rect.y = ptr->parent->rect.y + ptr->parent->content.padding;
  }
  else if (ptr->prev){
    if (stacking) { // atp it's a sibling so it has previous and has width
      ptr->rect.y = ptr->prev->rect.y + ptr->prev->rect.height + ptr->gap;
    } else {
      ptr->rect.x = ptr->prev->rect.x + ptr->prev->rect.width + ptr->gap;
    }
  }

  // setting the width assumes that the the children at the bottom have their dimensions declared

  // go down
  if (ptr->content.children){
    __UI_UpdateLayout__(ptr->content.children, ptr->content.stack_content);
    // set dimensions after acumulating 
    ptr->parent->rect.width = ptr->list_width;
    ptr->parent->rect.height = ptr->list_height;
  }

  // go left
  if (ptr->next){
    __UI_UpdateLayout__(ptr->next, stacking);

    // acumulate dimnsions
    if (stacking) {
      ptr->prev->list_width = MAX(ptr->list_width, ptr->prev->rect.width);
      ptr->prev->list_height += ptr->list_height;
    } else {
      ptr->prev->list_height = MAX(ptr->list_height, ptr->prev->rect.height);
      ptr->prev->list_width += ptr->list_width;
    }
  }
  else{
    ptr->list_width = ptr->rect.width;
    ptr->list_height = ptr->rect.height;
  }
}

void UI_UpdateLayout(UI_element* r){
  __UI_UpdateLayout__(r, false);
}

/* UI_element* UI_Icon(arena* a, struct Image icon){} */
/* UI_element* UI_InputBox(arena* a, string placeholder){} */
