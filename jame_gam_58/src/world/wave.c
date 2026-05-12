#include "wave.h"
#include "../entities/entities.h"
#include "map.h"

void _wave_next(WaveSystem* wave)
{
    wave->current_wave++;
    wave->spawn_timer = 5;
    wave->active = true;

    wave->enemies_spawned = 0;
    wave->enemies_to_spawn = wave->current_wave * 2;
}

void _spawn_random_enemy(WaveSystem* wave, Entities* e)
{
    wave->enemies_spawned++;
    wave->spawn_timer = (float)GetRandomValue(1, 5);

    // Future me add a random thingy to spawn enemies at random given parameters
    //spawn_smol_skeleton(&e->all, &e->needles, wave->next_pos);
    //spawn_fat_skeleton(&e->all, wave->next_pos);
    //spawn_fast_skeleton(&e->all, wave->next_pos);
    spawn_necromancer(&e->all, wave->next_pos);
}

void wave_update(WaveSystem* wave, Map* map, Entities* e, float dt)
{
    if (IsKeyPressed(KEY_N))
        _wave_next(wave);

    int active_enemies = 0;
    for (size_t i = 0; i < e->all.count; i++)
    {
        Entity* ent = &e->all.data[i];
        if (ent->active && ent->type != ENTITY_PLAYER)
            active_enemies++;
    }

    if (wave->enemies_spawned >= wave->enemies_to_spawn
            && active_enemies == 0
            && wave->active)
    {
        _wave_next(wave);
        // Delete all entities except for the player on new wave
        e->all.count = 1;
        e->needles.count = 1;
        return;
    }

    if (wave->enemies_spawned < wave->enemies_to_spawn
            && wave->active)
    {
        static bool got_next_pos = false;
        if (got_next_pos == false)
        {
            got_next_pos = true;
            wave->next_pos = (Vector2) {
                .x = (float)GetRandomValue(-map->size.x / 2, map->size.x / 2),
                .y = (float)GetRandomValue(-map->size.y / 2, map->size.y / 2),
            };
        }

        float radius = 64 * (wave->spawn_timer / 5.0f);
        DrawCircleLines(wave->next_pos.x, wave->next_pos.y, radius, RED);

        wave->spawn_timer -= dt;
        if (wave->spawn_timer <= 0)
        {
            _spawn_random_enemy(wave, e);
            got_next_pos = false;
        }
    }
}
