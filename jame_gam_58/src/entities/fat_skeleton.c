#include "fat_skeleton.h"
#include "entities.h"
#include "utils.h"
#include <raymath.h>

void spawn_fat_skeleton(EntityList* list, Vector2 pos)
{
    Entity e = {
        .type = ENTITY_FAT_SKELETON,
        .pos = pos,
        .health = 10,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {
                .x = 24,
                .y = 24,
            },
            .mass = 2,
            .radius = 24,
        },
    };

    DA_APPEND(list, e);
}

void ai_fat_skeleton(Entity* skeleton, Entity* player, float dt)
{
    const float ACCELERATION = 500;

    Vector2 dir = Vector2Subtract(player->pos, skeleton->pos);
    dir = Vector2Normalize(dir);

    skeleton->vel.x += dir.x * ACCELERATION * dt;
    skeleton->vel.y += dir.y * ACCELERATION * dt;
}
