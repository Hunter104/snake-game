#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "snake.h"

Vector2 getNewFruit(Snake *snake) {
  bool isInsideSnake = false;
  Vector2 position = { 0 };
  do {
    position.x = GetRandomValue(0, horizontal_tiles-1);
    position.y =  GetRandomValue(0, vertical_tiles-1);

    for (int i=0; i<snake->len; i++) {
      if (Vector2Equals(position, snake->segments[i]))   {
        isInsideSnake = true;
        break;
      }
    }
  } while (isInsideSnake);

  return position;
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Snake Game");

    float timeSinceLastMove = 0.0f;
    SetTargetFPS(60);               

    Vector2 middle = {(float) horizontal_tiles/2, (float) vertical_tiles/2};
    Snake *snake = CreateSnake(middle);
    Vector2 fruitPosition = getNewFruit(snake);

    bool gameEnd = false;
    while (!gameEnd)   
    {
        if (WindowShouldClose()) gameEnd = true;

        int KeyPressed = GetKeyPressed();
        while (KeyPressed != 0) {
          Vector2 direction = GetDirection(KeyPressed);
          if (isValidDirection(snake, direction)) 
            SetFacing(snake, direction);

          KeyPressed = GetKeyPressed();
        } 

        timeSinceLastMove += GetFrameTime();
        if (timeSinceLastMove >= tickDelay) {
          MoveSnake(snake);
          snake->directionLocked = false;
          if (IsSnakeColliding(snake))
            gameEnd = true;
          timeSinceLastMove = 0;
        }

        if (Vector2Equals(snake->segments[0], fruitPosition)) {
          append(snake);
          fruitPosition = getNewFruit(snake);
        }
        BeginDrawing();
        Vector2 fruitCoords = TiletoCartesian(fruitPosition);
        DrawRectangle(fruitCoords.x, fruitCoords.y, tileSize-tilePadding, tileSize-tilePadding, RED);
        DrawSnake(snake);
        ClearBackground(BLACK);
        EndDrawing();
    }
    
    freeSnake(snake);
    CloseWindow();        
    return 0;
}
