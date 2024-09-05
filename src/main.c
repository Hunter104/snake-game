#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "snake.h"
#include "tilefuncs.h"
#include "main.h"

GameState *initializeGame(void) {
    GameState *game = malloc(sizeof *game);
    game->timeSinceLastMovement = 0.0f;
    game->gameOver = false;
    game->snakeTurnLock = false;
    game->lastDirection = Vector2Zero();

    Vector2 middle = {(float) horizontal_tiles/2, (float) vertical_tiles/2};
    game->snake = CreateSnake(middle);
    InitWindow(screenWidth, screenHeight, "Snake Game");

    updateFruitLocation(game);
    SetTargetFPS(60);               

    return game;
}

void endGame(GameState *game) {
  freeSnake(game->snake);
  free(game);
}

void updateFruitLocation(GameState *game) {
  Vector2 position = Vector2Zero();
  do {
    position.x = GetRandomValue(0, horizontal_tiles-1);
    position.y = GetRandomValue(0, vertical_tiles-1);
  } while (isInsideSnake(position, game->snake));
  game->fruitPosition = position;
}

bool isInsideSnake(Vector2 vector, Snake *snake) {
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
    return UPVector;
  if (key == KEY_DOWN || key == KEY_S)
    return DownVector;

  return Vector2Zero();
}

void handleInput(GameState *game) {
    int KeyPressed = GetKeyPressed();
    while (KeyPressed != 0) {
      game->lastDirection = GetDirection(KeyPressed); 
      KeyPressed = GetKeyPressed();
    } 
}

void updateGame(GameState *game) {
    game->timeSinceLastMovement += GetFrameTime();

    if (game->timeSinceLastMovement >= tickDelay) {
      SetFacing(game->snake, game->lastDirection);
      MoveSnake(game->snake);
      if (IsSnakeColliding(game->snake))
        game->gameOver = true;

      game->timeSinceLastMovement = 0;
    }

    if (Vector2Equals(game->snake->segments[0], game->fruitPosition)) {
      append(game->snake);
      updateFruitLocation(game);
    }
}

void render(GameState *game) {
    BeginDrawing();

    Vector2 fruitCoords = TiletoCartesian(game->fruitPosition);
    DrawRectangle(fruitCoords.x, fruitCoords.y, tileSize-tilePadding, tileSize-tilePadding, RED);
    DrawSnake(game->snake);

    ClearBackground(BLACK);
    EndDrawing();
}


int main(void)
{
    GameState *game = initializeGame();
    while (!game->gameOver)   
    {
        if (WindowShouldClose()) game->gameOver = true;
        handleInput(game);
        updateGame(game);
        render(game);
    }
    
    endGame(game);
    CloseWindow();        
    return 0;
}
