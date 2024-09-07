#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "constants.h"
#include "snake.h"
#include "main.h"
#include "memory_utils.h"
#include "apple.h"

GameState *InitializeGame(void) {
    GameState *game = safeMalloc(sizeof *game);
    game->timeSinceLastMovement = 0.0f;
    game->gameOverFlag = false;
    game->snakeTurnLockFlag = false;
    game->lastDirection = UP;

    Vector2 middle = {(float) WIDTH_TILES/2, (float) HEIGHT_TILES/2};
    game->snake = CreateSnake(middle);
    InitWindow(WIDTH_CARTESIAN, HEIGHT_CARTESIAN, "Snake Game");

    game->apple = GetNewApple(game->snake);
    SetTargetFPS(FPS);               

    return game;
}

void EndGame(GameState *game) {
  FreeSnake(game->snake);
  free(game);
}

static Directions GetDirection(int key) {
  switch (key) {
    case KEY_RIGHT:
    case KEY_D:
      return RIGHT;
    case KEY_LEFT:
    case KEY_A:
      return LEFT;
    case KEY_UP:
    case KEY_W:
      return UP;
    case KEY_DOWN:
    case KEY_S:
      return DOWN;
    default:
      return INVALID;
  }
}

void HandleInput(GameState *game) {
    int KeyPressed = GetKeyPressed();
    if (KeyPressed == NO_KEY_PRESSED) return;
    Directions direction = GetDirection(KeyPressed); 
    if (direction == INVALID) return;
    game->lastDirection = direction;
}

void UpdateGame(GameState *game) {
    game->timeSinceLastMovement += GetFrameTime();

    if (game->timeSinceLastMovement >= TICK_DELAY) {
      SetFacing(game->snake, game->lastDirection);
      MoveSnake(game->snake);
      if (IsSnakeSelfColliding(game->snake) || IsSnakeOutOfBounds(game->snake))
        game->gameOverFlag = true;

      game->timeSinceLastMovement = 0;
    }

    if (Vector2Equals(game->snake->head->position, game->apple)) {
      GrowSnake(game->snake);
      game->apple = GetNewApple(game->snake);
    }
}

void RenderGame(GameState *game) {
    BeginDrawing();

    RenderApple(game->apple);
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
