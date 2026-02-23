#include "../core/include/core.h"
#include <stdio.h>

void* dosomething(void* elem){
  UI_element* e = (UI_element*)elem;
  e->rect.x += 50;
  e->rect.y += 50;
  printf("pisso");

  return NULL;  
}

void printUI(UI_element r, int level){
  printf("%d ", level); printf("%s\n", r.id.str);
  if(r.parent)
    printf("%5s parent: %s\n", "", r.parent->id.str);
  if(r.prev)
    printf("%5s sibling: %s\n", "", r.prev->id.str);
  printf("%5s x: %f\n", "", r.rect.x);
  printf("%5s y: %f\n", "", r.rect.y);
  printf("%5s w: %f\n", "", r.rect.width);
  printf("%5s gaps: %d\n", "", r.gap);

  puts("");

  if(r.content.children) printUI(*r.content.children, level+1);

  if(r.next) printUI(*r.next, level);
}

UI_root TEST_ui() {
  puts("UI TESTS");
  arena a = ARENA_Init();
  UI_root root = UI_Init(&a);

  root.root->content.padding = 5;
  root.root->content.children_gap = 5;

  /* UI_element* container1 = UI_InitElement(root.a); */
  /* container1->content.padding = 5; */
  /* container1->rect.width = 10; */
  /* container1->id = STR("container1"); */

  UI_element* container2 = UI_InitElement(root.a);
  container2->content.padding = 5;
  container2->content.children_gap = 5;
  container2->id = STR("container2");

  UI_element* butt1 = UI_TextButton(root.a, STR("click me"));
  butt1->id = STR("button1");
  butt1->click_args = (void*)butt1;
  butt1->onClick_left = dosomething;

  UI_element* butt2 = UI_TextButton(root.a, STR("do not"));
  butt2->id = STR("button2");
  butt2->click_args = (void*)butt2;
  butt2->onClick_left = dosomething;

  UI_element* container3 = UI_InitElement(root.a);
  container3->content.padding = 5;
  container3->id = STR("container3");

  UI_element* butt3 = UI_TextButton(root.a, STR("do not"));
  butt3->id = STR("button3");
  butt3->onClick_left = dosomething;

  UI_AppendChild( root.root, container2);
  /* UI_AppendElement( container1, container2); */
  UI_AppendChild( container2, butt1);
  UI_AppendChild( container2, butt2);
  UI_AppendChild( container2, container3);
  UI_AppendChild( container3, butt3);

  UI_UpdateLayout(root.root);  

  printUI(*root.root, 1);

  return root;
}

void TEST_arena(){
  puts("ARENA TESTS");
  arena a = ARENA_Init();

  string s = ARENA_strcpy(&a, STR("coucouc"));
  string ss = ARENA_strcpy(&a, STR("cacac"));
  string sss = ARENA_strcpy(&a, STR("cicic"));

  printf("custom text here: %s, %s, %s\n", s.str, ss.str, sss.str);  

  ARENA_Reset(&a);
}

void TEST_display(){
    InitWindow(800, 450, "raylib [core] example - basic window");

    UI_root root = TEST_ui();

    while (!WindowShouldClose()) {
        BeginDrawing();
	    ClearBackground(RAYWHITE);
	    DISPLAY_RenderUI(*root.root);
        EndDrawing();
    }

    CloseWindow();

    return;
}

int main(){
  TEST_arena();
  puts("-----------");
  TEST_ui();
  puts("-----------");
  TEST_display();

  return 0;  
}
