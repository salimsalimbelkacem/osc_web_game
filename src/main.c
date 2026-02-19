#include <raylib.h>
#include <emscripten/emscripten.h>

const int screenWidth = 1280;
const int screenHeight = 720;

void UpdateDrawFrame();

/* Notes about the programing logic
 * - no local state, but API interactions
 * - example: discovering something that would unclock a dialogue
 *   > instead of using a local player state like checking if an
 *     object is in the inventory during the dialogue loop,
 *     we directly set the node to unlocked during the picking up function
 */

// TODO: implement display modes
// - menu mode
//   > pause menu mode
//   > main menu mode
// - game mode
//   > game scene + hud overlay
//   > inventory menu mode
//   > dialogue menu mode

// TODO: implement a way to switch between those modes
// - maybe have a display function for each individual mode,
//   then have a variable pointing to the current loop mode,
//   and that variable changes inside those modes
//   and have it called here maybe maybe
//   emscripten_set_main_loop( currentMode, 0, 1);

int main() {
    InitWindow(screenWidth, screenHeight, "coucou");

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    CloseWindow();
    return 0;
}

void UpdateDrawFrame() {

    BeginDrawing();
        ClearBackground(RAYWHITE);
    EndDrawing();
}
