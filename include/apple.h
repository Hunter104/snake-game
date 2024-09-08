#pragma once
#include "snake.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

typedef Vector2 Apple;

/* Game must be initialized
 * Can theoretically run forever
 * Snake as parameter so apple doesn't spawn on top of it
 */
Apple GetNewApple(Snake *snake);
void RenderApple(Apple apple);
