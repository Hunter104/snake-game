#pragma once
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "apple.h"
#include "snake.h"

typedef struct GameState {
  Snake *snake;
  Apple apple;
  Vector2 lastDirection;
  float timeSinceLastMovement;
  bool gameOverFlag;
  bool snakeTurnLockFlag;
} GameState;

Vector2 GetDirection(int key);
bool IsInsideSnake(Vector2 vector, Snake *snake);
void HandleInput(GameState *game); 
void UpdateGame(GameState *game); 
void RenderGame(GameState *game); 
GameState *InitializeGame(void); 
void EndGame(GameState *game); 
