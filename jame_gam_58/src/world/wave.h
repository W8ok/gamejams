#pragma once

#include <stdbool.h>
#include <raylib.h>

typedef struct WaveSystem {
    int current_wave;
    int enemies_to_spawn;
    int enemies_spawned;

    Vector2 next_pos;

    float spawn_timer;
    bool active;
} WaveSystem;

struct Map;
struct Entities;
void wave_update(WaveSystem* wave, struct Map* map, struct Entities* e, float dt);
