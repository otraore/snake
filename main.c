#include "snake.h"

Vector2 foodPositionEaten ={ -1, -1 };

int main()
{
    Color foodColor = YELLOW;

    Vector2 unitSizeV ={ (float)unitSize, (float)unitSize };

    struct Snake snake ={
        .direction = RIGHT,
        .color = WHITE,
        .movePeriod = 7,
        .moveCounter= 0,
        .nSegments = 1,
        .units = unitSize,
        .maxSegments = gridSize,
        .deltaLocation = (Vector2){ 1, 0 },
        .segments[0] = (Vector2){ 10, 10 },
    };

    growSnake(&snake);
    growSnake(&snake);
    growSnake(&snake);

    InitWindow(screenWidth, screenHeight, "snake");
    Vector2 foodPosition = randomPosition(gridWidth, gridHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (snake.direction == LEFT || snake.direction == RIGHT) {
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) snake.direction = UP;
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) snake.direction = DOWN;
        }
        else {
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) snake.direction = RIGHT;
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) snake.direction = LEFT;
        }

        moveSnake(&snake);

        // if food is eaten, find a new random position that's not in the snake
        if (Vector2Equals(snake.segments[0], foodPosition)) {
            while (Vector2Equals(foodPosition, foodPositionEaten)) {
                foodPosition = randomPosition(gridWidth, gridHeight);
                if (Vector2Equals(snake.segments[0], foodPosition)) {
                    foodPosition = foodPositionEaten;
                    growSnake(&snake);
                }
                // do check if it's in snake
            }

        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < snake.nSegments; ++i) {
            Vector2 seg = snake.segments[i];
            seg.x *= snake.units;
            seg.y *= snake.units;
            DrawRectangleV(seg, unitSizeV, snake.color);
        }

        DrawRectangleV(Vector2Multiply(foodPosition, unitSizeV), unitSizeV, foodColor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

