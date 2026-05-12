#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "utils.h"
#include "player.h"
#include "entities.h"

void spawn_player(Entities* e, NeedleList* needles)
{
    Entity p = {
        .type = ENTITY_PLAYER,
        .pos = {0, 0},
        .vel = {0, 0},
        .health = 10,
        .active = true,
        .needle_inside = false,
        .hitbox = {
            .offset = {16, 16},
            .mass = 1,
            .radius = 16,
        },
        .needle_id = needles->count,
        .has_needle = true,
    };
    
    e->player_idx = e->all.count;

    Needle needle = {
        .type = NEEDLE_NONE,
        .thickness = 8,
        .parent_idx = e->all.count,
        .active = true,
    };

    spawn_needle(needles, needle);

    DA_APPEND(&e->all, p);
}

void player_render(Texture2D* tex, Entity* p, float dt)
{
    // DO NOT judge my horror of an animation system :3

    static int state = 0;
    static float animation_timer = 0.1;

    bool moving = (p->vel.x != 0 || p->vel.y != 0);

    int direction = 0; // down
    if (p->vel.y < 0)
        direction = 1; // up

    if (moving)
    {
        animation_timer -= dt;

        if (animation_timer <= 0)
        {
            animation_timer = 0.5;

            // Alternate between 1 and 2
            if (state == 1)
                state = 2;
            else
                state = 1;
        }
    }
    else
    {
        // Idle frame
        state = 0;
    }

    const float SPRITE_SIZE = 32;
    Rectangle src = {
        .x = SPRITE_SIZE * direction,
        .y = SPRITE_SIZE * state,
        .width = SPRITE_SIZE,
        .height = SPRITE_SIZE,
    };

    const float SIZE = 64;
    Rectangle dst = {
        .x = p->pos.x,
        .y = p->pos.y,
        .width = SIZE,
        .height = SIZE,
    };

    Vector2 origin = p->hitbox.offset;

    DrawTexturePro(*tex, src, dst, origin, 0, WHITE);
}

void player_control(Entity* p, Needle* n, float dt)
{
    const float ACCELERATION = 1500;

    if (IsKeyDown(KEY_W))
        p->vel.y -= ACCELERATION * dt;
    if (IsKeyDown(KEY_A))
        p->vel.x -= ACCELERATION * dt;
    if (IsKeyDown(KEY_S))
        p->vel.y += ACCELERATION * dt;
    if (IsKeyDown(KEY_D))
        p->vel.x += ACCELERATION * dt;

    if (IsKeyDown(KEY_ONE))
    {
        n->type = NEEDLE_NONE;
        n->active = false;
    }
    else if (IsKeyDown(KEY_TWO))
    {
        n->type = NEEDLE_SHORT;
        n->active = true;
    }
    else if (IsKeyDown(KEY_THREE))
    {
        n->type = NEEDLE_LONG;
        n->active = true;
    }
}
