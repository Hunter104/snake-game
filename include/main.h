#pragma once
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "snake.h"

typedef struct GameState {
  Snake *snake;
  Vector2 fruitPosition;
  Vector2 lastDirection;
  float timeSinceLastMovement;
  bool gameOver;
  bool snakeTurnLock;
} GameState;

Vector2 GetDirection(int key);
bool isInsideSnake(Vector2 vector, Snake *snake);
void updateFruitLocation(GameState *game); 
void handleInput(GameState *game); 
void updateGame(GameState *game); 
void render(GameState *game); 
GameState *initializeGame(void); 
void endGame(GameState *game); 
