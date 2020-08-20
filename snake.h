#include "raylib.h"
#include "raymath.h"
#include <math.h>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define gridWidth 30
#define gridHeight 30
#define unitSize 20
#define screenWidth (gridWidth * unitSize)
#define screenHeight (gridHeight * unitSize)
#define gridSize (gridWidth * gridHeight)

enum Direction
{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Snake
{
    enum Direction direction;
    enum Direction nextDirection;
    Color color;
    int startingLength;
    int movePeriod;
    int moveCounter;
    int units;
    int nSegments;
    int maxSegments;
    bool gameOver;
    Vector2 foodPosition;
    Vector2 foodPositionEaten;
    Vector2 deltaLocation;
    Vector2 segments[gridSize];
};

void moveSnake(struct Snake *snake);
void followSegment(struct Snake *snake, int startIndex, int endIndex);
void move(struct Snake *snake);
void growSnake(struct Snake *snake);
void foodCheck(struct Snake *snake);
bool insideGrid(Vector2);
bool insideSnake(struct Snake *snake, Vector2 position);
Vector2 randomPosition(int cols, int rows);
bool Vector2Equals(Vector2 a, Vector2 b);

#endif //SNAKE_SNAKE_H
