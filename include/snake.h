#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#define INITIAL_CAPACITY 20

typedef Vector2 Segment;

typedef struct Snake {
  int capacity;
  int len;
  Vector2 *segments;
  Vector2 facing;
  bool directionLocked;
} Snake;

Snake *CreateSnake(Vector2 position); 
void freeSnake(Snake *snake); 
void SetFacing(Snake *snake, Vector2 direction); 
void MoveSnake(Snake *snake); 
bool IsSnakeColliding(Snake *snake); 
void append(Snake *snake); 
void DrawSnake(Snake *snake); 

