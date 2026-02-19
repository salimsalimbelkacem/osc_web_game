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

/* TODO: implement action hooks system
   - functions and code to execute before doing any action
   - API to add and remove hooks from an action
 */

struct object {

};


/* TODO: implement a datastructure for inventory
 * maybe just an array/map of objects
 */

struct inventory {

};

/* TODO: a dialogue system?
   - tree? each interlocutor has it's own?
   - dialogue node? character to player
   > character's replique
   > options
   >> player's replique
   >> next dialogue node
   > boolean was visited
   > locked/unlocked (invisible option)
 */

struct dialogue_tree {

};

/* TODO: dialogue states API
   - lock/unlock options
 */

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

/*  TODO: implement functions for
    - initializing scenes
    - changing scenes
 */

struct scene {

};

/* TODO: implement a datastructure for player
   - inventory
   - curent scene
*/
