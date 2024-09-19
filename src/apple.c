#include "apple.h"
#include "constants.h"
#include "snake.h"
#include "tilefuncs.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

static bool IsInsideSnake(Apple apple, Segment *tail) {
  for (Segment *current = tail; current != NULL; current = current->prev)
    if (Vector2Equals(apple, current->position))
      return true;

  return false;
}

/* Game must be initialized
 * Can theoretically run forever
 * Snake as parameter so apple doesn't spawn on top of it
 */
Apple GetNewApple(Snake *snake) {
  Apple newApple = Vector2Zero();
  do {
    newApple.x = (float) GetRandomValue(0, WIDTH_TILES - 1);
    newApple.y = (float) GetRandomValue(0, HEIGHT_TILES - 1);
  } while (IsInsideSnake(newApple, snake->tail));
  return newApple;
}

void RenderApple(Apple apple) {
  Vector2 fruitCoords = TiletoCartesian(apple);
  DrawRectangle((int) fruitCoords.x, (int) fruitCoords.y, TILE_SIZE - TILE_PADDING,
                TILE_SIZE - TILE_PADDING, RED);
}
