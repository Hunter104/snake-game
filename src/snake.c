#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "tilefuncs.h"
#include "snake.h"
#define INITIAL_CAPACITY 20

Snake *CreateSnake(Vector2 position) {
  Snake *snake = malloc(sizeof *snake);
  if (!snake)
    abort();
  snake->capacity = INITIAL_CAPACITY*sizeof(Vector2);
  snake->len = 1;
  Vector2 *segments = malloc(snake->capacity);
  if (!segments)
    abort();
  snake->segments = segments;
  snake->facing = RightVector;
  snake->segments[0] = position;
  snake->directionLocked = false;

  return snake;
}

void freeSnake(Snake *snake) {
  free(snake->segments);
  free(snake);
}

Vector2 GetDirection(int key) {
  if (key == KEY_RIGHT)
    return RightVector;
  if (key == KEY_LEFT)
    return LeftVector;
  if (key == KEY_UP)
    return UPVector;
  if (key == KEY_DOWN)
    return DownVector;

  return Vector2Zero();
}

bool isValidDirection(Snake *snake, Vector2 direction) {
  bool noDirection = Vector2Equals(direction, Vector2Zero());
  bool willStop = Vector2Equals(Vector2Add(snake->facing, direction), Vector2Zero());
  
  return !(noDirection || willStop);
}

void SetFacing(Snake *snake,  Vector2 direction) {
  if (snake->directionLocked)
    return;
  bool noDirection = Vector2Equals(direction, Vector2Zero());
  bool willStop = Vector2Equals(Vector2Add(snake->facing, direction), Vector2Zero());
  if (noDirection || willStop)
    return;

  snake->facing = direction;
  snake->directionLocked = true;
}

void MoveSnake(Snake *snake) {
  Vector2 *segments = snake->segments;
  for (int i=snake->len-1; i > 0; i--) 
    segments[i] = segments[i-1]; 
  segments[0] = Vector2Add(segments[0], snake->facing);
}

bool IsSnakeColliding(Snake *snake) {
  Vector2 snakePosition = snake->segments[0];
  bool outOfBounds = (snakePosition.x < 0 || snakePosition.x > horizontal_tiles ||
                      snakePosition.y < 0 || snakePosition.y > vertical_tiles);

  bool collision = false;
  for (int i=1; i < snake->len; i++) {
    if (Vector2Equals(snakePosition, snake->segments[i]))
    {
      collision = true;
      break;
    } 
  }

  return collision || outOfBounds;
}

void append(Snake *snake) {
  if (snake->len >= snake->capacity) {
    snake->capacity *= 2;
    snake->segments = realloc(snake->segments, snake->capacity);
    if (!snake->segments)
      abort();
  }
  snake->segments[snake->len] = snake->segments[snake->len-1];
  snake->len++;
}

void DrawSnake(Snake *snake) {
  for (int i=0; i<snake->len; i++) {
    Vector2 coords = TiletoCartesian(snake->segments[i]);
    DrawRectangle(coords.x, coords.y, tileSize-tilePadding, tileSize-tilePadding, GREEN);
  }
}

