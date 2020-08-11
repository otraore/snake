#include "raylib.h"
#include "snake.h"
#include "raymath.h"
#include <math.h>

Vector2 foodPositionEaten = {-1, -1};

int main()
{
    Color foodColor = YELLOW;

    Vector2 unitSizeV = {(float)unitSize, (float)unitSize};


    snake.direction = RIGHT;
    snake.color = WHITE;
    snake.movePeriod = 7;
    snake.moveCounter= 0;
    snake.nSegments = 1;
    snake.units = unitSize;
    snake.maxSegments = gridSize;
    snake.deltaLocation = (Vector2){1, 0};
    snake.segments[0] = (Vector2){ 10, 10};

    growSnake(&snake);
    growSnake(&snake);
    growSnake(&snake);

    InitWindow(screenWidth, screenHeight, "snake");
    Vector2 foodPosition = randomPosition(gridWidth, gridHeight);

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(snake.direction == LEFT || snake.direction == RIGHT) {
            if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) snake.direction = UP;
            if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) snake.direction = DOWN;
        } else {
            if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) snake.direction = RIGHT;
            if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) snake.direction = LEFT;
        }

        moveSnake(&snake);

        // if food is eaten, find a new random position that's not in the snake
        if(Vector2Equals(snake.segments[0], foodPosition)) {
            while (Vector2Equals(foodPosition, foodPositionEaten)) {
                foodPosition = randomPosition(gridWidth, gridHeight);
                if(Vector2Equals(snake.segments[0], foodPosition)) {
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

void moveSnake(struct Snake *snake) {
    switch (snake->direction) {
        case UP:
            snake->deltaLocation = (Vector2){0, -1};
            break;
        case DOWN:
            snake->deltaLocation = (Vector2){0, 1};
            break;
        case LEFT:
            snake->deltaLocation = (Vector2){-1, 0};
            break;
        case RIGHT:
            snake->deltaLocation = (Vector2){1, 0};
            break;
    }

    ++snake->moveCounter;
    if(snake->moveCounter >= snake->movePeriod) {
        snake->moveCounter = 0;
        moveBy(snake);
    }


//    if(snakePosition.x > (float)(screenWidth - units) || snakePosition.x < 0) {
//        snakePosition.x = initialPosition.x;
//    }
//
//    if(snakePosition.y < 0 || snakePosition.y > (float)(screenHeight - units)) {
//        snakePosition.y = initialPosition.y;
//    }
}

Vector2 randomPosition(int cols, int rows) {
     Vector2 pos = { floor(GetRandomValue(0, cols - 1)) , floor(GetRandomValue(0, rows - 1))};
    return pos;
}

bool Vector2Equals(Vector2 a, Vector2 b) {
    return a.x == b.x && a.y == b.y;
}

void followSegment(struct Snake *snake, int startIndex, int endIndex) {
    snake->segments[startIndex] = snake->segments[endIndex];
}

void moveBy(struct Snake *snake) {
    for (int i = snake->nSegments - 1; i > 0; i--) {
        followSegment(snake, i, i - 1);

    }
    snake->segments[0].x += snake->deltaLocation.x;
    snake->segments[0].y += snake->deltaLocation.y;
}

void growSnake(struct Snake *snake) {
    if(snake->nSegments < snake->maxSegments) {
        snake->nSegments++;
    }
}
