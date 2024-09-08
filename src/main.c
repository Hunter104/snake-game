#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "constants.h"
#include "snake.h"
#include "memory_utils.h"
#include "apple.h"

typedef struct GameData {
  int points;
  Snake *snake;
  Apple apple;
  Directions lastDirection;
  float timeSinceLastMovement;
  bool gameOverFlag;

  Sound fxPickUp;
  Sound fxGameOver;
} GameData;

GameData *InitializeGame(void) {
    GameData *game = safeMalloc(sizeof *game);
    game->timeSinceLastMovement = 0.0f;
    game->gameOverFlag = false;
    game->lastDirection = UP;

    Vector2 middle = {(float) WIDTH_TILES/2, (float) HEIGHT_TILES/2};
    game->snake = CreateSnake(middle);
    InitWindow(WIDTH_CARTESIAN, HEIGHT_CARTESIAN, "Snake Game");
    InitAudioDevice();
    game->apple = GetNewApple(game->snake);
    SetTargetFPS(FPS);               
    game->fxPickUp = LoadSound("assets/pick-up.ogg");
    game->fxGameOver = LoadSound("assets/game-over.ogg");

    return game;
}

void EndGame(GameData *game) {
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

void HandleInput(GameData *game) {
    int KeyPressed = GetKeyPressed();
    if (KeyPressed == NO_KEY_PRESSED) return;
    Directions direction = GetDirection(KeyPressed); 
    if (direction == INVALID) return;
    game->lastDirection = direction;
}

void UpdateGame(GameData *game) {
    game->timeSinceLastMovement += GetFrameTime();

    if (game->timeSinceLastMovement >= TICK_DELAY) {
      SetFacing(game->snake, game->lastDirection);
      MoveSnake(game->snake);
      if (IsSnakeSelfColliding(game->snake) || IsSnakeOutOfBounds(game->snake)) {
        game->gameOverFlag = true;
        PlaySound(game->fxGameOver);
      }

      game->timeSinceLastMovement = 0;
    }

    if (Vector2Equals(game->snake->head->position, game->apple)) {
      PlaySound(game->fxPickUp);
      GrowSnake(game->snake);
      game->points++;
      game->apple = GetNewApple(game->snake);
    }
}

// TODO: Parametrize colors
void RenderScoreboard(GameData *game) {
  // HACK: fontSize must be constant
  int fontSize = HEIGHT_CARTESIAN*0.7;
  const char *text = TextFormat("%i", game->points);
  float textWidth = MeasureText(text, fontSize);
  DrawText(text, WIDTH_CARTESIAN*0.5-(textWidth/2) + 5, HEIGHT_CARTESIAN*0.5-(fontSize/2) + 5, fontSize, Fade(DARKGRAY, 0.5f)); // Shadow
  DrawText(text, WIDTH_CARTESIAN*0.5-(textWidth/2), HEIGHT_CARTESIAN*0.5-(fontSize/2), fontSize, GRAY);  // Main text
}

void RenderGame(GameData *game) {
    BeginDrawing();

    RenderScoreboard(game);
    RenderApple(game->apple);
    RenderSnake(game->snake);

    ClearBackground(BLACK);
    EndDrawing();
}

int main(void)
{
    GameData *game = InitializeGame();
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
