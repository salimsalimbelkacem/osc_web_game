#include <raylib.h>
#include "arena.h"

typedef enum {
    UI_STATE_NONE = 0,
    UI_STATE_HOVERED = 1 << 0,
    UI_STATE_CLICKED = 1 << 1,
    UI_STATE_VISIBLE = 1 << 2
} UI_Flags;


typedef enum {  UI_BG_NONE, UI_BG_COLOR, UI_BG_TEXTURE} UI_Bg_Type;

typedef enum { UI_CONTENT_NONE, UI_CONTENT_TEXT, UI_CONTENT_IMAGE, UI_CONTENT_CHILDREN} UI_Content_Type;
typedef enum { UI_CONTENT_ALIGN_LEFT, UI_CONTENT_ALIGN_CENTER, UI_CONTENT_ALIGN_RIGHT} UI_Content_HAlign_Type;
typedef enum { UI_CONTENT_ALIGN_TOP, UI_CONTENT_ALIGN_MIDDLE, UI_CONTENT_ALIGN_BOTTOM} UI_Content_VAlign_Type;

typedef void (*UI_Action)(struct UI_element*);

typedef struct UI_element {
  struct Rectangle area;

  UI_Action onClick_left;
  UI_Action onClick_right;
  UI_Action onClick_middle;
  UI_Action onHover;

  u16 state;
  u16 layer;

  struct UI_element* next;

  struct UI_Background{
    UI_Bg_Type type;
    u8 alpha;

    union {Color color; Texture texture;};
  } bg;

  struct UI_Border{
    UI_Bg_Type type;
    u8 alpha;
    u8 width;
    
    union {struct Color color; struct Texture texture;};
  } border;

  struct UI_Content {
    UI_Content_Type type;
    UI_Content_HAlign_Type h_align;
    UI_Content_VAlign_Type v_align;

    u16 padding;    
    u16 children_gap;    
    bool stack_content;    

    union {
      struct {
        string content; u8 font_size; // add font?
        } text;

      struct Image Image;
      struct {
        UI_element *children;
	u8 count;
        } children;
      };

  } content;
} UI_element;

typedef struct {
  arena a;
  UI_element* root;
} UI_root;

UI_root UI_Init();
UI_element* UI_InitElement( vec2 coord, arena* a);

void UI_AppendElement(UI_element* e, UI_element* new_e);
void UI_PopElement(UI_element* e, UI_element* new_e);
void UI_AppendChild(UI_element* parent);
void UI_PopChild(UI_element* parent); // should pop all sub-children obviously


UI_element* UI_Button(string text);
UI_element* UI_Textbox(string text);
UI_element* UI_Icon(struct Image icon);
UI_element* UI_InputBox(string placeholder); // do i need this?

void UI_ElementSetState();
void UI_ElementUnsetState();
