//
// Created by Ousmane on 09/08/2020.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
enum Direction {
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};


void moveSnake(enum Direction direction, int units, float speed);
Vector2 randomPosition(int width, int height, int units);

#endif //SNAKE_SNAKE_H
