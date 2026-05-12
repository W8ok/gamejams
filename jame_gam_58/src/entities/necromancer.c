#include "necromancer.h"
#include "entities.h"
#include "utils.h"
#include <raymath.h>

void spawn_necromancer(EntityList* list, Vector2 pos)
{
    Entity e = {
        .type = ENTITY_NECROMANCER,
        .pos = pos,
        .health = 3,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {
                .x = 8,
                .y = 8,
            },
            .mass = 1,
            .radius = 8,
        },
    };

    DA_APPEND(list, e);
}

void _ai_movement(Entity* e, Entity* player, float dt)
{
    const float ACCELERATION = 1000.0f;

    const float MIN_DIST = 250.0f;
    const float MAX_DIST = 300.0f;

    Vector2 to_player = Vector2Subtract(player->pos, e->pos);

    float dist = Vector2Length(to_player);

    // Avoid divide-by-zero
    if (dist <= 0.001f)
        return;

    Vector2 dir = Vector2Scale(to_player, 1.0f / dist);

    if (dist > MAX_DIST)
    {
        e->vel.x += dir.x * ACCELERATION * dt;
        e->vel.y += dir.y * ACCELERATION * dt;
    }
    else if (dist < MIN_DIST)
    {
        e->vel.x -= dir.x * ACCELERATION * dt;
        e->vel.y -= dir.y * ACCELERATION * dt;
    }
}

void ai_necromancer(Entity* e, Entity* player, float dt, EntityList* list)
{
    _ai_movement(e, player, dt);

    if (list->count > 200)
        return;
    
    static float time_till_next_summon = 1;
    time_till_next_summon -= dt;
    if (time_till_next_summon <= 0)
    {
        spawn_fast_skeleton(list, e->pos);
        time_till_next_summon = (float)GetRandomValue(1, 5);
    }
}
