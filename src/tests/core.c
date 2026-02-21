#include "../core/include/core.h"
#include <stdio.h>

void dosomething(){
  printf("pisso");
}

void printUI(UI_element r, int level){
  printf("%d ", level);
  printf("%s\n", r.id.str);
  printf("%10s x: %f\n", "", r.rect.x);
  printf("%10s y: %f\n", "", r.rect.y);
  printf("%10s w: %f\n", "", r.rect.width);
  printf("%10s gaps: %d\n", "", r.gap);

  if(r.content.children) printUI(*r.content.children, level+1);
  if(r.next) printUI(*r.next, level);
}

void TEST_ui() {

  arena a = ARENA_Init();
  UI_root root = UI_Init(&a);

  root.root->content.padding = 5;
  root.root->content.children_gap = 5;

  UI_element* container1 = UI_InitElement(root.a);
  container1->content.padding = 5;
  container1->rect.width = 10;
  container1->id = STR("container1");

  UI_element* container2 = UI_InitElement(root.a);
  container2->content.padding = 5;
  container2->id = STR("container2");

  UI_element* butt1 = UI_TextButton(root.a, STR("click me"));
  butt1->id = STR("button1");
  butt1->onClick_left = dosomething;

  UI_AppendChild( root.root, container1);
  UI_AppendElement( container1, container2);
  UI_AppendChild( container2, butt1);

  UI_UpdateLayout(root.root);  

  printUI(*root.root, 1);
}

void TEST_arena(){
  arena a = ARENA_Init();

  string s = ARENA_strcpy(&a, STR("couocu"));

  printf("custom text here: %s\n", s.str);  
}

int main(){
  TEST_arena();
  TEST_ui();

  return 0;  
}
