#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "apple.h"
#include "tilefuncs.h"


static bool IsInsideTiles(Apple apple, Vector2 *tiles, int n) {
  for (int i=0; i<n; i++) 
    if (Vector2Equals(apple, tiles[i]))
      return true;

  return false;
}

/* Game must be initialized
 * Can theoretically run forever
*/
Apple GetNewApple(Vector2 *noSpawnZones, int n) {
  Apple newApple = Vector2Zero();
  do {
    newApple.x = GetRandomValue(0, WIDTH_TILES-1);
    newApple.y = GetRandomValue(0, HEIGHT_TILES-1);
  } while (IsInsideTiles(newApple, noSpawnZones, n));
  return newApple;
}

void RenderApple(Apple apple) {
    Vector2 fruitCoords = TiletoCartesian(apple);
    DrawRectangle(fruitCoords.x, fruitCoords.y, TILE_SIZE-TILE_PADDING, TILE_SIZE-TILE_PADDING, RED);
}

