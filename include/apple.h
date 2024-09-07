#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

typedef Vector2 Apple;

Apple GetNewApple(Vector2 *noSpawnZones, int n);
void RenderApple(Apple apple);

