#include <raylib.h>
#include "entities/entities.h"
#include "world/world.h"

int main(void)
{
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(1280, 720, "game");

    Entities e = {0};
    World w = {0};

    entity_init(&e);
    world_init(&w);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        entity_update(&e, dt);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(10, 10);

        entity_render(&e);

        map_render(&w.map);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
