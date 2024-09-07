#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "tilefuncs.h"
#include "snake.h"
#include "memory_utils.h"
#define INITIAL_CAPACITY 20

static Segment *CreateSegment(Vector2 position) {
  Segment *segment = safeMalloc(sizeof *segment);
  segment->position = position;
  segment->prev = NULL;

  return segment;
}

Snake *CreateSnake(Vector2 position) {
  Snake *snake = safeMalloc(sizeof *snake);
  snake->head = CreateSegment(position);
  snake->tail = snake->head;
  snake->facing = UP_VECTOR;

  return snake;
}

void FreeSnake(Snake *snake) {
  Segment *current = snake->head;
  while (current != NULL) {
    Segment *tmp = current;
    current = current->next;
    free(tmp);
  }
  free(snake);
}

// TODO: Create datatype for valid directions
void SetFacing(Snake *snake,  Vector2 direction) {
  if (Vector2Equals(direction, Vector2Zero()) || 
      Vector2Equals(Vector2Add(snake->facing, direction), Vector2Zero()))
    return;

  snake->facing = direction;
}

// TODO: Create function for checking if out of bounds
static Vector2 WrapPosition(Vector2 position) {
  if (position.x < 0) position.x = WIDTH_TILES-1;
  if (position.x >= WIDTH_TILES) position.x = 0;
  if (position.y < 0) position.y = HEIGHT_TILES-1;
  if (position.y >= HEIGHT_TILES) position.y = 0;

  return position;
}

void MoveSnake(Snake *snake) {
  for (Segment *current=snake->tail; current != snake->head; current=current->prev) 
    current->position = current->prev->position; 

  // Move snake forward forward
  snake->head->position = WrapPosition(Vector2Add(snake->head->position, snake->facing));
}

bool IsSnakeSelfColliding(Snake *snake) {
  for (Segment *current=snake->tail; current != snake->head; current=current->prev)
    if (Vector2Equals(snake->head->position, current->position))
      return true;

  return false;
}

void GrowSnake(Snake *snake) {
  Segment *newSegment = CreateSegment(snake->tail->position);
  newSegment->prev = snake->tail;
  snake->tail = newSegment;
}

void RenderSnake(Snake *snake) {
  for (Segment *current=snake->tail; current != NULL; current=current->prev) {
    Vector2 coords = TiletoCartesian(current->position);
    DrawRectangle(coords.x, coords.y, TILE_SIZE-TILE_PADDING, TILE_SIZE-TILE_PADDING, GREEN);
  }
}

