#pragma once
#include <raylib.h>

typedef enum Directions { UP = 0, DOWN, LEFT, RIGHT, INVALID } Directions;
#define FPS 60
#define NO_KEY_PRESSED 0

#define TILE_PADDING 0
#define TILE_SIZE 40
#define HEIGHT_TILES 20
#define WIDTH_TILES 20

#define WIDTH_CARTESIAN (WIDTH_TILES * TILE_SIZE)
#define HEIGHT_CARTESIAN (HEIGHT_TILES * TILE_SIZE)

#define TICK_DELAY 0.1f

extern const Vector2 SCREEN_MIDDLE_TILES;
extern const Vector2 DIRECTIONS_MAP[4];
