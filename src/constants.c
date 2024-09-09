#include "constants.h"
#include <raylib.h>
#include <raymath.h>

const int FPS = 60;
const int NO_KEY_PRESSED = 0;

const Vector2 DIRECTIONS_MAP[4] = {
    {0.0f, -1.0f},
    {0.0f, 1.0f},
    {-1.0f, 0.0f},
    {1.0f, 0.0f},
};

const int TILE_PADDING = 0;
const int TILE_SIZE = 40;
const int HEIGHT_TILES = 20;
const int WIDTH_TILES = 20;

const float WIDTH_CARTESIAN = WIDTH_TILES * TILE_SIZE;
const float HEIGHT_CARTESIAN = HEIGHT_TILES * TILE_SIZE;

const float TICK_DELAY = 0.1f;

const Vector2 SCREEN_MIDDLE_TILES = {(float)(WIDTH_TILES / 2) - 1,
                                     (float)(HEIGHT_TILES / 2) - 1};
