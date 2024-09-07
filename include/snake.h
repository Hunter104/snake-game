#pragma once
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#define INITIAL_CAPACITY 20

typedef struct Segment {
  Vector2 position;
  struct Segment *next;
  struct Segment *prev;
} Segment;

typedef struct Snake {
  Segment *head;
  Segment *tail;
  Vector2 facing;
  bool directionLocked;
} Snake;

Snake *CreateSnake(Vector2 position); 
void FreeSnake(Snake *snake); 
void SetFacing(Snake *snake, Vector2 direction); 
void MoveSnake(Snake *snake); 
bool IsSnakeSelfColliding(Snake *snake); 
void GrowSnake(Snake *snake); 
void RenderSnake(Snake *snake); 

