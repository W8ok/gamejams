#include <raylib.h>
#include "../entities/entities.h"
#include "camera.h"

void campera_update(Camera2D* cam, Entity* p, float dt)
{
    Vector2 desired = {
        .x = p->pos.x + p->hitbox.offset.x,
        .y = p->pos.y + p->hitbox.offset.y
    };

    const float t = 5; 

    cam->target.x += (desired.x - cam->target.x) * t * dt;
    cam->target.y += (desired.y - cam->target.y) * t * dt;

    cam->offset = (Vector2){
        .x = (float)GetScreenWidth() / 2,
        .y = (float)GetScreenHeight() / 2
    };

    cam->rotation = 0;
    cam->zoom = 1;
}

void camera_init(Camera2D* cam, Entity* p)
{
    cam->target = (Vector2) {
        .x = p->pos.x + p->hitbox.offset.x,
        .y = p->pos.y + p->hitbox.offset.y
    };
    
    cam->offset = (Vector2){
        .x = (float)GetScreenWidth() / 2,
        .y = (float)GetScreenHeight() / 2
    };

    cam->rotation = 0;
    cam->zoom = 1;
}
