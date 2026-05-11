#include <raylib.h>
#include <raymath.h>
#include "entities.h"
#include "collisions.h"

void collide_needle_entity(Entity* e, Needle* needle)
{
    if (!e->active
            || !needle->active
            || e->type == ENTITY_PLAYER)
        return;

    Vector2 center = {
        e->pos.x + e->hitbox.offset.x,
        e->pos.y + e->hitbox.offset.y,
    };

    bool inside = CheckCollisionCircleLine(
        center,
        e->hitbox.radius + needle->thickness * 0.5f,
        needle->start,
        needle->end
    );

    if (inside && !e->needle_inside)
    {
        e->needle_inside = true;
        e->health--;

        const float KNOCKBACK_FORCE = 300.0f;
        e->vel = Vector2Add(
            e->vel,
            Vector2Scale(needle->dir, KNOCKBACK_FORCE / e->hitbox.mass)
        );
    }
    else if (!inside)
    {
        e->needle_inside = false;
    }

    if (e->health <= 0)
    {
        e->active = false;
    }
}

static void _bounce(Entity* a, Entity* b)
{
    float total_mass = a->hitbox.mass + b->hitbox.mass;
    Vector2 a_vel = a->vel;
    
    a->vel = Vector2Scale(b->vel, (2 * b->hitbox.mass) / total_mass);
    b->vel = Vector2Scale(a_vel, (2 * a->hitbox.mass) / total_mass);
}

void entity_inter_collision(EntityList* list)
{
    if (list->count < 2)
        return;

    for (size_t i = 0; i < list->count; i++)
    {
        for (size_t j = i + 1; j < list->count; j++)
        {
            Entity* a = &list->data[i];
            Entity* b = &list->data[j];

            if (!a->active || !b->active)
                continue;

            if (!CheckCollisionCircles(
                        Vector2Add(a->pos, a->hitbox.offset), a->hitbox.radius, 
                        Vector2Add(b->pos, b->hitbox.offset), b->hitbox.radius))
                continue;

            // Massive fucking nested switch statements go brrrrrr
            switch (a->type)
            {
                default: _bounce(a, b); break;

                case ENTITY_PLAYER:
                    switch (b->type)
                    {
                        default: _bounce(a, b); break;
                    }
                    break;

                case ENTITY_TRAINING_DUMMY:
                    switch (b->type)
                    {
                        default: _bounce(a, b); break;
                    }
                    break;
            }
        }
    }
}
