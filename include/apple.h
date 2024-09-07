#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "snake.h"

typedef Vector2 Apple;

Apple GetNewApple(Snake *snake);
void RenderApple(Apple apple);

