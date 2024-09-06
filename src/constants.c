#include <raylib.h>
#include <raymath.h>
#include "constants.h"

const Vector2 UpVector = {(float) 0, (float)-1};
const Vector2 DownVector = {(float) 0, (float)1};
const Vector2 LeftVector = {(float) -1, (float)0};
const Vector2 RightVector = {(float) 1, (float)0};
const int tileSize = 20;
const int verticalTiles = 40;
const int horizontalTiles = 40;
const int screenWidth = horizontalTiles*tileSize;
const int screenHeight = verticalTiles*tileSize;
const float tickDelay = 0.1f;
const int tilePadding = 5;
