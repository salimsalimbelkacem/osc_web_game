#include <raylib.h>
#include <emscripten/emscripten.h>

const int screenWidth = 1280;
const int screenHeight = 720;

void UpdateDrawFrame();

/* Notes about the programing logic
 * - no local state, but API interactions
 *   example: discovering something that would unclock a dialogue
 *   > instead of using a local player state like checking if an
 *     object is in the inventory during the dialogue loop,
 *     we directly set the node to unlocked during the picking up function
 */


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
