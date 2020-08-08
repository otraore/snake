#include "raylib.h"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "snake");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hello World", 190, 200, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}