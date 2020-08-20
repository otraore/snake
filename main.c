#include "snake.h"
#include "stdio.h"

int main()
{
    Color foodColor = YELLOW;

    Vector2 unitSizeV = {(float)unitSize, (float)unitSize};

    struct Snake snake = {
        .nextDirection = RIGHT,
        .direction = RIGHT,
        .color = WHITE,
        .startingLength = 3,
        .movePeriod = 6,
        .moveCounter = 0,
        .nSegments = 1,
        .units = unitSize,
        .maxSegments = gridSize,
        .gameOver = false,
        .foodPositionEaten = (Vector2){-1, -1},
        .deltaLocation = (Vector2){0, 0},
        .segments[0] = (Vector2){10, 10},
    };
    for (int i = 0; i < snake.startingLength; i++)
    {
        growSnake(&snake);
    }

    InitWindow(screenWidth, screenHeight, "snake");
    snake.foodPosition = randomPosition(gridWidth, gridHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        if (snake.direction == LEFT || snake.direction == RIGHT)
        {
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
                snake.nextDirection = UP;
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
                snake.nextDirection = DOWN;
        }
        else
        {
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
                snake.nextDirection = RIGHT;
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
                snake.nextDirection = LEFT;
        }

        moveSnake(&snake);
        foodCheck(&snake);

        BeginDrawing();
        ClearBackground(BLACK);
        if (!snake.gameOver)
        {
            for (int i = 0; i < snake.nSegments; ++i)
            {
                Vector2 seg = snake.segments[i];
                seg.x *= snake.units;
                seg.y *= snake.units;
                DrawRectangleV(seg, unitSizeV, snake.color);
            }

            DrawRectangleV(Vector2Multiply(snake.foodPosition, unitSizeV), unitSizeV, foodColor);
        }
        else
        {
            DrawText("GAME OVER!", 160, 250, 40, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
