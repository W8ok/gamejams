#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "needle.h"
#include "entities.h"
#include "utils.h"

void spawn_needle(NeedleList* needles, Needle needle)
{
    DA_APPEND(needles, needle);
}

void needle_render(NeedleList* needles)
{
    for (size_t i = 0; i < needles->count; i++)
    {
        Needle* n = &needles->data[i];

        if (!n->active)
            continue;

        float angle = atan2f(n->dir.y, n->dir.x) * RAD2DEG;
        float length = Vector2Distance(n->start, n->end);
        Vector2 center = {
            (n->start.x + n->end.x) / 2,
            (n->start.y + n->end.y) / 2,
        };

        Rectangle rect = {
            center.x,
            center.y,
            length,
            n->thickness,
        };

        Vector2 origin = {
            length / 2,
            n->thickness / 2,
        };

        DrawRectanglePro(rect, origin, angle, GRAY);
    }
}

extern Camera2D cam;
static void _needle_follow_mouse(Entity* player, Needle* needle)
{
    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), cam);

    Vector2 size = {
        player->hitbox.offset.x * 2,
        player->hitbox.offset.y * 2
    };

    Vector2 center = {
        player->pos.x + size.x * 0.5f,
        player->pos.y + size.y * 0.5f
    };

    Vector2 dir = {
        mouse.x - center.x,
        mouse.y - center.y
    };

    needle->dir = Vector2Normalize(dir);
}

static void _needle_follow_player(Entity* player, Entity* e, Needle* needle)
{
    Vector2 center = Vector2Add(e->pos, e->hitbox.offset);
    Vector2 target = Vector2Add(player->pos, player->hitbox.offset);
    Vector2 dir = Vector2Subtract(target, center);

    needle->dir = Vector2Normalize(dir);
}

void needle_update(Entity* player, Entity* e, NeedleList* needles)
{
    Needle* needle = &needles->data[e->needle_id];

    if (!needle->active)
        return;

    Vector2 size = {
        e->hitbox.offset.x * 2,
        e->hitbox.offset.y * 2
    };

    Vector2 center = {
        e->pos.x + size.x * 0.5f,
        e->pos.y + size.y * 0.5f
    };

    // choose behavior
    if (e->type == ENTITY_PLAYER)
        _needle_follow_mouse(e, needle);
    else
        _needle_follow_player(player, e, needle);

    float length = 0;
    switch (needle->type)
    {
        case NEEDLE_NONE:  length = 0;  break;
        case NEEDLE_SHORT: length = 30; break;
        case NEEDLE_LONG:  length = 60; break;
    }

    needle->start = center;
    needle->end = (Vector2){
        center.x + needle->dir.x * length,
        center.y + needle->dir.y * length
    };
}
