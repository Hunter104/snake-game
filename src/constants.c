#include <raylib.h>
#include <raymath.h>
#include "constants.h"

const int FPS = 60;
const int NO_KEY_PRESSED = 0;

const Vector2 UP_VECTOR = {0.0f, -1.0f};
const Vector2 DOWN_VECTOR = {0.0f, 1.0f};
const Vector2 LEFT_VECTOR = {-1.0f, 0.0f};
const Vector2 RIGHT_VECTOR = {1.0f, 0.0f};

const int TILE_PADDING = 5;
const int TILE_SIZE = 40;
const int HEIGHT_TILES = 20;
const int WIDTH_TILES = 20;

const int WIDTH_CARTESIAN = WIDTH_TILES*TILE_SIZE;
const int HEIGHT_CARTESIAN = HEIGHT_TILES*TILE_SIZE;

const float TICK_DELAY = 0.1f;
