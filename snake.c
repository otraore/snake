#include "snake.h"

void moveSnake(struct Snake *snake)
{
    ++snake->moveCounter;
    if (snake->moveCounter >= snake->movePeriod)
    {
        snake->direction = snake->nextDirection;
        switch (snake->direction)
        {
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
        snake->moveCounter = 0;
        move(snake);
    }
}

Vector2 randomPosition(int cols, int rows)
{
    Vector2 pos = {floor(GetRandomValue(0, cols - 1)), floor(GetRandomValue(0, rows - 1))};
    return pos;
}

bool Vector2Equals(Vector2 a, Vector2 b)
{
    return a.x == b.x && a.y == b.y;
}

void followSegment(struct Snake *snake, int startIndex, int endIndex)
{
    snake->segments[startIndex] = snake->segments[endIndex];
}

void move(struct Snake *snake)
{
    for (int i = snake->nSegments - 1; i > 0; i--)
    {
        followSegment(snake, i, i - 1);
    }

    Vector2 *head = &snake->segments[0];
    head->x += snake->deltaLocation.x;
    head->y += snake->deltaLocation.y;

    // check to see if outside grid or head is inside of the body
    if (!insideGrid(*head) || insideSnake(snake, snake->segments[0]))
    {
        snake->gameOver = true;
    }
}

// checks to see if head is at food position, and if so eats the food growing the snake
// also repositions the food to another random location outside of the snake body
void foodCheck(struct Snake *snake)
{
    // if food is eaten, find a new random position that's not in the snake
    if (Vector2Equals(snake->segments[0], snake->foodPosition))
    {
        growSnake(snake);
        snake->foodPosition = snake->foodPositionEaten;

        while (Vector2Equals(snake->foodPosition, snake->foodPositionEaten))
        {
            snake->foodPosition = randomPosition(gridWidth, gridHeight);
            if (insideSnake(snake, snake->foodPosition))
            {
                snake->foodPosition = snake->foodPositionEaten;
                growSnake(snake);
            }
        }
    }
}
// grows the snake by one
void growSnake(struct Snake *snake)
{
    if (snake->nSegments < snake->maxSegments)
    {
        Vector2 currentTail = snake->segments[snake->nSegments - 1];
        snake->nSegments++;
        switch (snake->direction)
        {
        case UP:
            snake->segments[snake->nSegments - 1] = (Vector2){currentTail.x, currentTail.y + 1};
            break;
        case DOWN:
            snake->segments[snake->nSegments - 1] = (Vector2){currentTail.x, currentTail.y - 1};
            break;
        case LEFT:
            snake->segments[snake->nSegments - 1] = (Vector2){currentTail.x + 1, currentTail.y};
            break;
        case RIGHT:
            snake->segments[snake->nSegments - 1] = (Vector2){currentTail.x - 1, currentTail.y};
            break;
        }
    }
}

// checks to see if position is inside of the snake body
bool insideSnake(struct Snake *snake, Vector2 position)
{
    for (int i = 1; i < snake->nSegments; i++)
    {
        if (Vector2Equals(position, snake->segments[i]))
        {
            return true;
        }
    }

    return false;
}

// checks if position is inside of the grid
bool insideGrid(Vector2 position)
{
    return position.x >= 0 && position.x < gridWidth && position.y >= 0 && position.y < gridHeight;
}