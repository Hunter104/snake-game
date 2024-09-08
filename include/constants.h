#pragma once
#include <raylib.h>

typedef enum Directions { UP = 0, DOWN, LEFT, RIGHT, INVALID } Directions;
extern const Vector2 SCREEN_MIDDLE_TILES;
extern const Vector2 DIRECTIONS_MAP[4];
extern const int NO_KEY_PRESSED;
extern const int FPS;
extern const Vector2 UP_VECTOR;
extern const Vector2 DOWN_VECTOR;
extern const Vector2 LEFT_VECTOR;
extern const Vector2 RIGHT_VECTOR;
extern const int TILE_SIZE;
extern const int HEIGHT_TILES;
extern const int WIDTH_TILES;
extern const int WIDTH_CARTESIAN;
extern const int HEIGHT_CARTESIAN;
extern const float TICK_DELAY;
extern const int TILE_PADDING;
