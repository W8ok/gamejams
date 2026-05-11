#include "entities.h"
#include "utils.h"

void entity_init(Entities* e)
{
    spawn_player(e, &e->needles);
    spawn_dummy(&e->all, (Vector2){300,300});
    spawn_smol_skeleton(&e->all, &e->needles, (Vector2){100,100});
}

void entity_update(Entities* e, float dt)
{
    Entity* player = &e->all.data[e->player_idx];

    player_control(player, &e->needles.data[player->needle_id], dt);

    for (size_t i = 0; i < e->all.count; i++)
    {
        Entity* ent = &e->all.data[i];

        if (!ent->active)
        {
            if (ent->has_needle)
                e->needles.data[ent->needle_id].active = false;

            continue;
        }

        if (ent->has_needle)
            needle_update(player, ent, &e->needles);

        collide_needle_entity(ent, &e->needles.data[player->needle_id]);
        entity_inter_collision(&e->all);

        const float DRAG = 5.0f;
        ent->vel.x -= ent->vel.x * DRAG * dt;
        ent->vel.y -= ent->vel.y * DRAG * dt;

        ent->pos.x += ent->vel.x * dt;
        ent->pos.y += ent->vel.y * dt;
    }
}

void entity_render(Entities* e)
{
    Entity* player = &e->all.data[e->player_idx];
    needle_render(&e->needles);

    for (size_t i = 0; i < e->all.count; i++)
    {
        Entity* ent = &e->all.data[i];
        if (!ent->active)
            continue;

        Vector2 size = {
            ent->hitbox.offset.x * 2,
            ent->hitbox.offset.y * 2,
        };

        Color color;
        switch (ent->type)
        {
            case ENTITY_NONE:               color = PINK;       break;
            case ENTITY_PLAYER:             color = RED;        break;
            case ENTITY_TRAINING_DUMMY:     color = YELLOW;     break;
            case ENTITY_SMOL_SKELETON:      color = WHITE;      break;
        }

        DrawRectangleV(e->all.data[i].pos, size, color);
    }
}
