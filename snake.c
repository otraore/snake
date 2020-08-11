#include "snake.h"

void moveSnake(struct Snake *snake) {
    switch (snake->direction) {
    case UP:
        snake->deltaLocation = (Vector2){ 0, -1 };
        break;
    case DOWN:
        snake->deltaLocation = (Vector2){ 0, 1 };
        break;
    case LEFT:
        snake->deltaLocation = (Vector2){ -1, 0 };
        break;
    case RIGHT:
        snake->deltaLocation = (Vector2){ 1, 0 };
        break;
    }

    ++snake->moveCounter;
    if (snake->moveCounter >= snake->movePeriod) {
        snake->moveCounter = 0;
        moveBy(snake);
    }
}

Vector2 randomPosition(int cols, int rows) {
    Vector2 pos ={ floor(GetRandomValue(0, cols - 1)), floor(GetRandomValue(0, rows - 1)) };
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
    if (snake->nSegments < snake->maxSegments) {
        snake->nSegments++;
    }
}
