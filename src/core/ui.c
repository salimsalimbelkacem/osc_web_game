// implement UI here

#include "include/ui.h"

//default ui styles
const u32 UI_DEF_FG_COLOR     = 0xc1c1c1;

const u32 UI_DEF_BG_COLOR     = 0x1e1e1e;
const u32 UI_DEF_BORDER_COLOR = 0xe1e1e1;

// text and heading;
const string UI_DEF_TXT_FONT     = STR("sans");
const u16 UI_DEF_TXT_FONT_SIZE   = 12;

const string UI_DEF_HEADING_FONT = STR("sans");
const u16 UI_DEF_H1_FONT_SIZE    = 24;
const u16 UI_DEF_H2_FONT_SIZE    = 20;
const u16 UI_DEF_H3_FONT_SIZE    = 16;

// buttons;
const i16 UI_DEF_BUTTON_WIDTH    = 50;
const i16 UI_DEF_BUTTON_HEIGHT   = 25;

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
  e->id = ARENA_strcpy(a, STR(""));

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
  new_e->gap = tail->gap;
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


UI_element* UI_TextButton(arena* a, string text){
  UI_element* butt = UI_InitElement(a);
  butt->type = UI_ELEMENT_BUTTON;

  butt->rect.width = UI_DEF_BUTTON_WIDTH;
  butt->rect.height = UI_DEF_BUTTON_HEIGHT;

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

  // set pos
  if (r->parent) { // checks if it's the first child
    r->rect.x = r->parent->rect.x + r->parent->content.padding;
    r->rect.y = r->parent->rect.y + r->parent->content.padding;

  } else if (r->prev) {
    if (stacking) { // atp it's a sibling so it has previous and has width
      r->rect.x = r->prev->rect.x;
      r->rect.y = r->prev->rect.y + r->prev->rect.height + r->gap;
    } else {
      r->rect.x = r->prev->rect.x + r->prev->rect.width + r->gap;
      r->rect.y = r->prev->rect.y;
      }
  }

  // go down
  if (r->content.children){
    __UI_UpdateLayout__(r->content.children, r->content.stack_content);
  }

  // go left
  else if (r->next){
    __UI_UpdateLayout__(r->next, stacking);

  } else {
    r->list_width = r->rect.width;
    r->list_height = r->rect.height;
  }

  if (r->parent) {
    r->parent->rect.width += r->list_width;
    r->parent->rect.height += r->list_height;
  } else if (r->prev) {
    if (stacking) {
      r->prev->list_width = MAX(r->list_width, r->prev->rect.width);
      r->prev->list_height += r->list_height + r->gap;
    } else {
      r->prev->list_height = MAX(r->list_height, r->prev->rect.height);
      r->prev->list_width += r->list_width + r->gap;
    }
  }
}

void UI_UpdateLayout(UI_element* r){
  __UI_UpdateLayout__(r, false);
}

/* UI_element* UI_Icon(arena* a, struct Image icon){} */
/* UI_element* UI_InputBox(arena* a, string placeholder){} */
