#pragma once
#include "snake.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

typedef Vector2 Apple;

Apple GetNewApple(Snake *snake);
void RenderApple(Apple apple);
