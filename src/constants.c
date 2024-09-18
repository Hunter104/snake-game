#include "constants.h"
#include <raylib.h>
#include <raymath.h>

const Vector2 DIRECTIONS_MAP[4] = {
    {0.0f, -1.0f},
    {0.0f, 1.0f},
    {-1.0f, 0.0f},
    {1.0f, 0.0f},
};

const Vector2 SCREEN_MIDDLE_TILES = {(float)(WIDTH_TILES / 2) - 1,
                                     (float)(HEIGHT_TILES / 2) - 1};
