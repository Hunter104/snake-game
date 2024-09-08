#include "apple.h"
#include "constants.h"
#include "memory_utils.h"
#include "snake.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum GameState { PLAYING, GAME_OVER } GameState;

typedef struct GameData {
  GameState currentState;

  int points;
  Snake *snake;
  Apple apple;
  Directions lastDirection;
  float timeSinceLastMovement;

  Sound fxPickUp;
  Sound fxGameOver;
} GameData;

GameData *InitializeGame(void) {
  GameData *game = safeMalloc(sizeof *game);

  InitWindow(WIDTH_CARTESIAN, HEIGHT_CARTESIAN, "Snake Game");
  InitAudioDevice();
  SetTargetFPS(FPS);

  game->currentState = PLAYING;

  game->points = 0;
  game->snake = CreateSnake(SCREEN_MIDDLE_TILES);
  game->apple = GetNewApple(game->snake);
  game->lastDirection = UP;
  game->timeSinceLastMovement = 0.0f;

  game->fxPickUp = LoadSound("assets/pick-up.ogg");
  game->fxGameOver = LoadSound("assets/game-over.ogg");

  return game;
}

void ResetGame(GameData *game) {
  game->points = 0;

  // HACK: not particurarly efficient
  FreeSnake(game->snake);
  game->snake = CreateSnake(SCREEN_MIDDLE_TILES);

  game->apple = GetNewApple(game->snake);
  game->currentState = PLAYING;
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

void HandleGameInput(GameData *game) {
  int KeyPressed = GetKeyPressed();
  if (KeyPressed == NO_KEY_PRESSED)
    return;
  Directions direction = GetDirection(KeyPressed);
  if (direction == INVALID)
    return;
  game->lastDirection = direction;
}

void UpdateGame(GameData *game) {
  game->timeSinceLastMovement += GetFrameTime();

  if (game->timeSinceLastMovement >= TICK_DELAY) {
    SetFacing(game->snake, game->lastDirection);
    MoveSnake(game->snake);
    if (IsSnakeSelfColliding(game->snake) || IsSnakeOutOfBounds(game->snake)) {
      game->currentState = GAME_OVER;
      PlaySound(game->fxGameOver);
      return;
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
  // TODO: Add a way to make font size get smaller the larger the number gets
  int fontSize = HEIGHT_CARTESIAN * 0.7;
  const char *text = TextFormat("%i", game->points);
  float textWidth = MeasureText(text, fontSize);
  DrawText(text, WIDTH_CARTESIAN * 0.5 - (textWidth / 2) + 5,
           HEIGHT_CARTESIAN * 0.5 - (fontSize / 2) + 5, fontSize,
           Fade(DARKGRAY, 0.5f)); // Shadow
  DrawText(text, WIDTH_CARTESIAN * 0.5 - (textWidth / 2),
           HEIGHT_CARTESIAN * 0.5 - (fontSize / 2), fontSize,
           Fade(GRAY, 0.5f)); // Main text
}
void RenderGridlines(int cellSize, Color color) {
  for (int x = 0; x <= WIDTH_CARTESIAN; x += cellSize)
    DrawLine(x, 0, x, HEIGHT_CARTESIAN, color);

  for (int y = 0; y <= HEIGHT_CARTESIAN; y += cellSize)
    DrawLine(0, y, WIDTH_CARTESIAN, y, color);
}

void RenderGame(GameData *game) {
  BeginDrawing();

  RenderScoreboard(game);

  // NOTE: Gridlines may not look that good
  RenderGridlines(TILE_SIZE, Fade(GREEN, 0.1f));
  RenderApple(game->apple);
  RenderSnake(game->snake);

  ClearBackground(BLACK);
  EndDrawing();
}

void HandleGameOverInput(GameData *game) {
  int key = GetKeyPressed();
  if (key == KEY_ENTER)
    ResetGame(game);
}

// TODO: place these screens definition sowhere
void RenderGameOverScreen(GameData *game) {
  BeginDrawing();

  // TODO: make gui wrapper
  int titleSize = 50;
  const char *title = "Game Over";
  float titleWidth = MeasureText(title, titleSize);

  int subtitleSize = 40;
  const char *subtitle = "Press enter to try again!";
  float subtitleWidth = MeasureText(subtitle, subtitleSize);

  // TODO: Update nvim sorround confing
  DrawText(title, (WIDTH_CARTESIAN - titleWidth) / 2,
           HEIGHT_CARTESIAN * 0.25 - titleSize / 2, titleSize, GRAY);
  DrawText(subtitle, (WIDTH_CARTESIAN - subtitleWidth) / 2,
           HEIGHT_CARTESIAN * 0.35 - subtitleSize / 2, subtitleSize, GRAY);

  ClearBackground(BLACK);
  EndDrawing();
}

int main(void) {
  GameData *game = InitializeGame();
  while (!WindowShouldClose()) {
    switch (game->currentState) {
    case PLAYING:
      HandleGameInput(game);
      UpdateGame(game);
      break;
    case GAME_OVER:
      HandleGameOverInput(game);
      break;
    }

    // Rendering
    switch (game->currentState) {
    case PLAYING:
      RenderGame(game);
      break;
    case GAME_OVER:
      RenderGameOverScreen(game);
      break;
    }
  }

  EndGame(game);
  CloseWindow();
  return 0;
}
