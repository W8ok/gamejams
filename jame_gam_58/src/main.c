#include <raylib.h>
#include "entities/entities.h"

int main(void)
{
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(1280, 720, "game");

    Entities e = {0};
    entity_init(&e);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        entity_update(&e, dt);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(10, 10);

        entity_render(&e);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
