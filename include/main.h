#pragma once
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "apple.h"
#include "constants.h"
#include "snake.h"

typedef struct GameState {
  Snake *snake;
  Apple apple;
  Directions lastDirection;
  float timeSinceLastMovement;
  bool gameOverFlag;
  bool snakeTurnLockFlag;
} GameState;

bool IsInsideSnake(Vector2 vector, Snake *snake);
void HandleInput(GameState *game); 
void UpdateGame(GameState *game); 
void RenderGame(GameState *game); 
GameState *InitializeGame(void); 
void EndGame(GameState *game); 
