#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#define INITIAL_CAPACITY 20

typedef struct Snake {
  size_t capacity;
  size_t len;
  Vector2 *segments;
  Vector2 facing;
  bool directionLocked;
} Snake;

Snake *CreateSnake(Vector2 position); 
void freeSnake(Snake *snake); 
Vector2 GetDirection(int key); 
bool isValidDirection(Snake *snake, Vector2 direction); 
void SetFacing(Snake *snake, Vector2 direction); 
void MoveSnake(Snake *snake); 
bool IsSnakeColliding(Snake *snake); 
void append(Snake *snake); 
void DrawSnake(Snake *snake); 

