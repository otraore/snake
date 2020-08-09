#include "raylib.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Vector2 snakePosition = {0, 0};
int unitSize = 20;
int screenWidth, screenHeight;
float snakeSpeed = 0.2f;

void moveSnake(enum Direction direction, int units, float speed) {
    Vector2 initialPosition = snakePosition;
    speed *= units;

    switch (direction) {
        case UP:
            snakePosition.y -= speed;
            break;
        case DOWN:
            snakePosition.y += speed;
            break;
        case LEFT:
            snakePosition.x -= speed;
            break;
        case RIGHT:
            snakePosition.x += speed;
            break;
    }

    if(snakePosition.x > (screenWidth - units) || snakePosition.x < 0) {
        snakePosition.x = initialPosition.x;
    }

    if(snakePosition.y < 0 || snakePosition.y > (screenHeight - units)) {
        snakePosition.y = initialPosition.y;
    }
}

int main()
{
    screenWidth = 30 * unitSize;
    screenHeight = 30 * unitSize;
    Color snakeColor = WHITE;
    Vector2 snakeUnitSizeV = {unitSize, unitSize};
    enum Direction startDirection = RIGHT;
    enum Direction currentDirection = startDirection;

    InitWindow(screenWidth, screenHeight, "snake");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(currentDirection == LEFT || currentDirection == RIGHT) {
            if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) currentDirection = UP;
            if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) currentDirection = DOWN;
        } else {
            if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) currentDirection = RIGHT;
            if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) currentDirection = LEFT;
        }
        moveSnake(currentDirection, unitSize, snakeSpeed);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleV(snakePosition, snakeUnitSizeV, snakeColor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}