#include "fast_skeleton.h"
#include "entities.h"
#include "utils.h"
#include <raymath.h>

void spawn_fast_skeleton(EntityList* list, Vector2 pos)
{
    Entity e = {
        .type = ENTITY_FAST_SKELETON,
        .pos = pos,
        .health = 1,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {
                .x = 4,
                .y = 4,
            },
            .mass = 0.3,
            .radius = 4,
        },
    };

    DA_APPEND(list, e);
}

void ai_fast_skeleton(Entity* skeleton, Entity* player, float dt)
{
    const float ACCELERATION = 1500;

    Vector2 dir = Vector2Subtract(player->pos, skeleton->pos);
    dir = Vector2Normalize(dir);

    skeleton->vel.x += dir.x * ACCELERATION * dt;
    skeleton->vel.y += dir.y * ACCELERATION * dt;
}
