#include "smol_skeleton.h"
#include "entities.h"
#include "utils.h"

void spawn_smol_skeleton(EntityList* list, NeedleList* needles, Vector2 pos)
{
    Entity e = {
        .type = ENTITY_SMOL_SKELETON,
        .pos = pos,
        .health = 3,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {
                .x = 8,
                .y = 8,
            },
            .mass = 0.5,
            .radius = 8,
        },
        .needle_id = needles->count,
        .has_needle = true,
    };

    Needle needle = {
        .type = NEEDLE_SHORT,
        .thickness = 4,
        .parent_idx = list->count,
        .active = true,
    };

    spawn_needle(needles, needle);

    DA_APPEND(list, e);
}
