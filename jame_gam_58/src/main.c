#include <raylib.h>
#include "entities/entities.h"
#include "world/world.h"
#include <stdio.h>

Camera2D cam;

int main(void)
{
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(1920, 1080, "game");

    Entities e = {0};
    World w = {0};

    entity_init(&e);
    world_init(&w);
    camera_init(&cam, &e.all.data[e.player_idx]);

    e.map = &w.map;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        entity_update(&e, dt);
        campera_update(&cam, &e.all.data[e.player_idx], dt);

        BeginDrawing();
        BeginMode2D(cam);

        ClearBackground(BLACK);

        wave_update(&w.wave, &w.map, &e, dt);

        entity_render(&e, dt);

        map_render(&w.map);

        EndMode2D();

        DrawFPS(10, 10);

        char entity_count[64];
        sprintf(entity_count, "Entites: %zu", e.all.count); 
        DrawText(entity_count, 10, 40, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
