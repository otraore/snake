//
// Created by Ousmane on 09/08/2020.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define gridWidth 30
#define gridHeight 30
#define unitSize  20
#define screenWidth ( gridWidth * unitSize)
#define screenHeight (gridHeight * unitSize)
#define gridSize (gridWidth * gridHeight)

enum Direction {
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Snake {
    enum Direction direction;
    Color color;
    int movePeriod;
    int moveCounter;
    int units;
    int nSegments;
    int maxSegments;
    Vector2 deltaLocation;
    Vector2 segments[gridSize];
};


struct Snake snake;
void moveSnake(struct Snake *snake);
void followSegment(struct Snake *snake, int startIndex, int endIndex);
void moveBy(struct Snake *snake);
void growSnake(struct Snake *snake);

Vector2 randomPosition(int cols, int rows);
bool Vector2Equals(Vector2 a, Vector2 b);

#endif //SNAKE_SNAKE_H
