#include <raylib.h>
#include <raymath.h>
#include "constants.h"

const Vector2 UPVector = {(float) 0, (float)-1};
const Vector2 DownVector = {(float) 0, (float)1};
const Vector2 LeftVector = {(float) -1, (float)0};
const Vector2 RightVector = {(float) 1, (float)0};
const int tileSize = 20;
const int vertical_tiles = 40;
const int horizontal_tiles = 40;
const int screenWidth = horizontal_tiles*tileSize;
const int screenHeight = vertical_tiles*tileSize;
const float tickDelay = 0.1f;
const int tilePadding = 5;
