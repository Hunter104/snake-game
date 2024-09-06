#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "tilefuncs.h"
#include "snake.h"
#include "memory_utils.h"
#define INITIAL_CAPACITY 20

Snake *CreateSnake(Vector2 position) {
  Snake *snake = safeMalloc(sizeof *snake);
  Segment *segments = safeMalloc(INITIAL_CAPACITY*sizeof(Segment));
  snake->capacity = INITIAL_CAPACITY;
  snake->len = 1;
  snake->segments = segments;
  snake->facing = RightVector;
  snake->segments[0] = position;

  return snake;
}

void FreeSnake(Snake *snake) {
  free(snake->segments);
  free(snake);
}

void SetFacing(Snake *snake,  Vector2 direction) {
  bool noDirection = Vector2Equals(direction, Vector2Zero());
  bool willStop = Vector2Equals(Vector2Add(snake->facing, direction), Vector2Zero());
  if (noDirection || willStop)
    return;

  snake->facing = direction;
}

void MoveSnake(Snake *snake) {
  Vector2 *segments = snake->segments;
  for (int i=snake->len-1; i > 0; i--) 
    segments[i] = segments[i-1]; 
  segments[0] = Vector2Add(segments[0], snake->facing);

  if (segments[0].x < 0) segments[0].x = horizontalTiles-1;
  if (segments[0].x >= horizontalTiles) segments[0].x = 0;
  if (segments[0].y < 0) segments[0].y = verticalTiles-1;
  if (segments[0].y >= verticalTiles) segments[0].y = 0;

}

bool IsSnakeColliding(Snake *snake) {
  Vector2 snakePosition = snake->segments[0];
  bool collision = false;
  for (int i=1; i < snake->len; i++) {
    if (Vector2Equals(snakePosition, snake->segments[i]))
    {
      collision = true;
      break;
    } 
  }

  return collision ;
}

void GrowSnake(Snake *snake) {
  if (snake->len >= snake->capacity) {
    snake->capacity *= 2;
    snake->segments = safeRealloc(snake->segments, snake->capacity*sizeof(Segment));
    if (!snake->segments)
      abort();
  }
  snake->segments[snake->len] = snake->segments[snake->len-1];
  snake->len++;
}

void RenderSnake(Snake *snake) {
  for (int i=0; i<snake->len; i++) {
    Vector2 coords = TiletoCartesian(snake->segments[i]);
    DrawRectangle(coords.x, coords.y, tileSize-tilePadding, tileSize-tilePadding, GREEN);
  }
}

