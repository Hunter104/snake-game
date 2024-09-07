#include "tilefuncs.h"
#include <raylib.h>
#include "constants.h"

Vector2 TiletoCartesian(Vector2 tilePos) {
  Vector2 Coords = {(tilePos.x*TILE_SIZE), (tilePos.y*TILE_SIZE)};
  return Coords;
}
