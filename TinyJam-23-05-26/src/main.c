#include <raylib.h>
#include <stdio.h>

#include "utils.h"
#include "app.h"
#include "node.h"

int main(void)
{
    App app;
    InitWindow(1280, 720, "CHOO!");

    while (!WindowShouldClose())
    {
        node_main(&app.nodes);

        BeginDrawing();
        ClearBackground(BLACK);

        for (size_t i = 0; i < app.nodes.count; i++)
        {
            Node node = app.nodes.data[i];
            DrawCircleV(node.pos, node.radius, RED);
        }

        EndDrawing();
    }

    printf("Train Sufficiently Choo'd\n");
    return 0;
}
