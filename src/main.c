#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "constants.h"
#include "snake.h"

typedef struct GameState {
  Snake *snake;
  Vector2 fruitPosition;
  float timeSinceLastMovement;
  bool gameOver;
} GameState;

void updateFruitLocation(GameState *game) {
  bool isInsideSnake = false;
  Vector2 position = { 0 };
  do {
    position.x = GetRandomValue(0, horizontal_tiles-1);
    position.y =  GetRandomValue(0, vertical_tiles-1);

    for (int i=0; i<game->snake->len; i++) {
      if (Vector2Equals(position, game->snake->segments[i]))   {
        isInsideSnake = true;
        break;
      }
    }
  } while (isInsideSnake);

  game->fruitPosition = position;
}

void handleInput(GameState *game) {
    int KeyPressed = GetKeyPressed();
    while (KeyPressed != 0) {
      Vector2 direction = GetDirection(KeyPressed);
      if (isValidDirection(game->snake, direction)) 
        SetFacing(game->snake, direction);

      KeyPressed = GetKeyPressed();
    } 
}

void updateGame(GameState *game) {
    game->timeSinceLastMovement += GetFrameTime();
    if (game->timeSinceLastMovement >= tickDelay) {
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

GameState *initializeGame(void) {
    GameState *game = malloc(sizeof *game);
    game->timeSinceLastMovement = 0.0f;
    game->gameOver = false;

    Vector2 middle = {(float) horizontal_tiles/2, (float) vertical_tiles/2};
    game->snake = CreateSnake(middle);
    updateFruitLocation(game);

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);               

    return game;
}

void endGame(GameState *game) {
  freeSnake(game->snake);
  free(game);
}

// TODO: Add queue to direction changes
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
