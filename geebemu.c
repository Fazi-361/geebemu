
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "GeeBEmu - Test raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib funziona!", 250, 200, 30, DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
