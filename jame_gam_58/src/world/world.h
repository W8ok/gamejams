#pragma once

#include "map.h"
#include "camera.h"
#include "wave.h"

typedef struct World {
    Map map;
    WaveSystem wave;
} World;

void world_init(World* w);
