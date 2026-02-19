#include <raylib.h>
#include <emscripten/emscripten.h>

const int screenWidth = 1280;
const int screenHeight = 720;

void UpdateDrawFrame();

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

