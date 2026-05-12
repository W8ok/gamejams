#include <raylib.h>
#include "entities/entities.h"
#include "world/world.h"

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
        campera_update(&cam, &e.all.data[e.player_idx], dt);

        entity_update(&e, dt);

        BeginDrawing();
        BeginMode2D(cam);

        ClearBackground(BLACK);

        wave_update(&w.wave, &w.map, &e, dt);

        entity_render(&e, dt);

        map_render(&w.map);

        EndMode2D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
