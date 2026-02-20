// implement the game logic here

/*   TODO: implement a datastructure for objects
     object has:
     - behavior:
     > inspect()
     > pick_up()
     > use()
     - texture

    Notes:
    - maybe objects can be not just objects but like
      passage ways that change the scene
    - must find a way to handle not pick-up-able objects
 */

#include "def.h"

#define DIALOGUE_TREE_OPTIONS_SIZE 5
#define SCENE_OBJECT_SIZE 20
#define INVENTORY_SIZE 50

// instead of having an oop like action implementation
// why not have one factory ish function that maps enum codes 
// to a function call, like with a switch case

/* typedef void* objectAction(gameState); */

/* struct actions{ */
/*   void* (*action)(); */
/*   void* (*inspect)(); */
/*   void* (*pickUp)(); */
/*   void* (*use)(); */
/*   void* (*goTo)(); // change scene? */
/* }; */

struct object {
  string name;
  /* struct actions behavior; */
  /*texture? icon small */
  /*texture? icon medium */
  /*texture? icon big */
};

struct dialogue_Tree
{
  string char_response;
  struct {
    string player_response;
    struct dialogue_Tree* next;
    } options[DIALOGUE_TREE_OPTIONS_SIZE];

  bool visited;    
  bool locked;    
};


/* TODO: character system
 
 */

/* TODO: implement a datastructure for scenes
   scene has:
   - background texture
   - objects map
   > object
   > rectangle clickable zone
   - next scene?
 */


struct scene {
  string name;
  struct {
    struct object o;
    /* raylib rectangle clickable zone */
  } objects [SCENE_OBJECT_SIZE];

    /*raylib bg texture*/  
};

/* TODO: implement a datastructure for player
   - inventory
   - curent scene
*/

/* TODO: implement a datastructure for inventory
 * maybe just an array/map of objects
 */

typedef struct object inventory[INVENTORY_SIZE];

struct player {
  string name;
  inventory inventory;
  struct scene* current_scene;
};
