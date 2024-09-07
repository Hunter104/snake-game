#pragma once
#include "constants.h"
#include <raylib.h>
#include <raymath.h>
#define INITIAL_CAPACITY 20

typedef struct Segment {
  Vector2 position;
  struct Segment *prev;
} Segment;

typedef struct Snake {
  Segment *head;
  Segment *tail;
  Directions facing;
  bool directionLocked;
} Snake;

bool IsSnakeOutOfBounds(Snake *snake);
Snake *CreateSnake(Vector2 position); 
void FreeSnake(Snake *snake); 
void SetFacing(Snake *snake, Directions direction); 
void MoveSnake(Snake *snake); 
bool IsSnakeSelfColliding(Snake *snake); 
void GrowSnake(Snake *snake); 
void RenderSnake(Snake *snake); 
