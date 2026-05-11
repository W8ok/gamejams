#pragma once

#include <raylib.h>

typedef struct Map {
    Vector2 size;
} Map;

void map_render(Map* map);
