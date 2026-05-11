#pragma once

#include "map.h"

typedef struct World {
    Map map;
} World;

void world_init(World* w);
