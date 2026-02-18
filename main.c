#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

const int screenWidth = 1280;
const int screenHeight = 720;

void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "coucou");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);

    EndDrawing();
}
