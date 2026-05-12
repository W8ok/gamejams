#include "entities.h"
#include "utils.h"
#include "../world/map.h"

void entity_init(Entities* e)
{
    e->tex.player = LoadTexture("assets/player.png");

    spawn_player(e, &e->needles);
    //spawn_dummy(&e->all, (Vector2){300,300});
    //spawn_smol_skeleton(&e->all, &e->needles, (Vector2){500,500});
}

void _entity_ai(Entities* e, Entity* ent, float dt)
{
    Entity* player = &e->all.data[e->player_idx];
    switch (ent->type)
    {
        default: break;
        case ENTITY_SMOL_SKELETON: ai_smol_skeleton(ent, player, dt);
    }
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

        _entity_ai(e, ent, dt);

        const float DRAG = 5.0f;
        ent->vel.x -= ent->vel.x * DRAG * dt;
        ent->vel.y -= ent->vel.y * DRAG * dt;

        if (ent->vel.x > -0.1 && ent->vel.x < 0.1)
            ent->vel.x = 0;

        if (ent->vel.y > -0.1 && ent->vel.y < 0.1)
            ent->vel.y = 0;

        ent->pos.x += ent->vel.x * dt;
        ent->pos.y += ent->vel.y * dt;

        // Map bounds checking
        if (ent->pos.x >= e->map->size.x / 2 - ent->hitbox.offset.x * 2)
        {
            ent->pos.x = e->map->size.x / 2 - ent->hitbox.offset.x * 2;
            ent->vel.x = 0;
        }
        if (ent->pos.y >= e->map->size.y / 2 - ent->hitbox.offset.y * 2)
        {
            ent->pos.y = e->map->size.y / 2 - ent->hitbox.offset.y * 2;
            ent->vel.y = 0;
        }
        if (ent->pos.x <= -e->map->size.x / 2)
        {
            ent->pos.x = -e->map->size.x / 2;
            ent->vel.x = 0;
        }
        if (ent->pos.y <= -e->map->size.y / 2)
        {
            ent->pos.y = -e->map->size.y / 2;
            ent->vel.y = 0;
        }
    }
}

void entity_render(Entities* e, float dt)
{
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
            default: break;
            case ENTITY_NONE:               color = PINK;       break;
            case ENTITY_PLAYER:             player_render(&e->tex.player, &e->all.data[e->player_idx], dt); break;
            case ENTITY_TRAINING_DUMMY:     color = YELLOW;     break;
            case ENTITY_SMOL_SKELETON:      color = WHITE;      break;
        }

        DrawRectangleV(e->all.data[i].pos, size, color);
    }
}
