#include "utils.h"
#include "dummy.h"
#include "entities.h"

void spawn_dummy(EntityList* list, Vector2 pos)
{
    Entity e = {
        .type = ENTITY_TRAINING_DUMMY,
        .pos = pos,
        .health = 3,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {
                .x = 16,
                .y = 16,
            },
            .mass = 1,
            .radius = 16,
        },
    };

    DA_APPEND(list, e);
}
