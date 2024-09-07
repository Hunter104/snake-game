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
  snake->facing = RIGHT_VECTOR;
  snake->segments[0] = position;

  return snake;
}

void FreeSnake(Snake *snake) {
  free(snake->segments);
  free(snake);
}

void SetFacing(Snake *snake,  Vector2 direction) {
  if (Vector2Equals(direction, Vector2Zero()) || 
      Vector2Equals(Vector2Add(snake->facing, direction), Vector2Zero()))
    return;

  snake->facing = direction;
}

static Vector2 WrapPosition(Vector2 position) {
  if (position.x < 0) position.x = WIDTH_TILES-1;
  if (position.x >= WIDTH_TILES) position.x = 0;
  if (position.y < 0) position.y = HEIGHT_TILES-1;
  if (position.y >= HEIGHT_TILES) position.y = 0;

  return position;
}

void MoveSnake(Snake *snake) {
  for (int i=snake->len-1; i > 0; i--) 
    snake->segments[i] = snake->segments[i-1]; 

  snake->segments[0] = WrapPosition(Vector2Add(snake->segments[0], snake->facing));
}

bool IsSnakeSelfColliding(Snake *snake) {
  for (int i=1; i < snake->len; i++)
    if (Vector2Equals(snake->segments[0], snake->segments[i]))
      return true;

  return false;
}

void GrowSnake(Snake *snake) {
  if (snake->len >= snake->capacity) {
    snake->capacity *= 2;
    snake->segments = safeRealloc(snake->segments, snake->capacity*sizeof(Segment));
  }
  snake->segments[snake->len] = snake->segments[snake->len-1];
  snake->len++;
}

void RenderSnake(Snake *snake) {
  for (int i=0; i<snake->len; i++) {
    Vector2 coords = TiletoCartesian(snake->segments[i]);
    DrawRectangle(coords.x, coords.y, TILE_SIZE-TILE_PADDING, TILE_SIZE-TILE_PADDING, GREEN);
  }
}

