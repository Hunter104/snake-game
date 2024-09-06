#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "constants.h"
#include "snake.h"
#include "tilefuncs.h"
#include "main.h"
#include "memory_utils.h"

GameState *InitializeGame(void) {
    GameState *game = safeMalloc(sizeof *game);
    game->timeSinceLastMovement = 0.0f;
    game->gameOverFlag = false;
    game->snakeTurnLockFlag = false;
    game->lastDirection = Vector2Zero();

    Vector2 middle = {(float) horizontalTiles/2, (float) verticalTiles/2};
    game->snake = CreateSnake(middle);
    InitWindow(screenWidth, screenHeight, "Snake Game");

    UpdateFruitLocation(game);
    SetTargetFPS(60);               

    return game;
}

void EndGame(GameState *game) {
  FreeSnake(game->snake);
  free(game);
}

void UpdateFruitLocation(GameState *game) {
  Vector2 position = Vector2Zero();
  do {
    position.x = GetRandomValue(0, horizontalTiles-1);
    position.y = GetRandomValue(0, verticalTiles-1);
  } while (IsInsideSnake(position, game->snake));
  game->fruitPosition = position;
}

bool IsInsideSnake(Vector2 vector, Snake *snake) {
  for (int i=0; i<snake->len; i++) {
    if (Vector2Equals(vector, snake->segments[i]))   {
      return true;
    }
  }
  return false;
}

Vector2 GetDirection(int key) {
  if (key == KEY_RIGHT || key == KEY_D)
    return RightVector;
  if (key == KEY_LEFT || key == KEY_A)
    return LeftVector;
  if (key == KEY_UP || key == KEY_W)
    return UpVector;
  if (key == KEY_DOWN || key == KEY_S)
    return DownVector;

  return Vector2Zero();
}

void HandleInput(GameState *game) {
    int KeyPressed = GetKeyPressed();
    while (KeyPressed != 0) {
      game->lastDirection = GetDirection(KeyPressed); 
      KeyPressed = GetKeyPressed();
    } 
}

void UpdateGame(GameState *game) {
    game->timeSinceLastMovement += GetFrameTime();

    if (game->timeSinceLastMovement >= tickDelay) {
      SetFacing(game->snake, game->lastDirection);
      MoveSnake(game->snake);
      if (IsSnakeColliding(game->snake))
        game->gameOverFlag = true;

      game->timeSinceLastMovement = 0;
    }

    if (Vector2Equals(game->snake->segments[0], game->fruitPosition)) {
      GrowSnake(game->snake);
      UpdateFruitLocation(game);
    }
}

void RenderGame(GameState *game) {
    BeginDrawing();

    Vector2 fruitCoords = TiletoCartesian(game->fruitPosition);
    DrawRectangle(fruitCoords.x, fruitCoords.y, tileSize-tilePadding, tileSize-tilePadding, RED);
    RenderSnake(game->snake);

    ClearBackground(BLACK);
    EndDrawing();
}


int main(void)
{
    GameState *game = InitializeGame();
    while (!game->gameOverFlag)   
    {
        if (WindowShouldClose()) game->gameOverFlag = true;
        HandleInput(game);
        UpdateGame(game);
        RenderGame(game);
    }
    
    EndGame(game);
    CloseWindow();        
    return 0;
}
