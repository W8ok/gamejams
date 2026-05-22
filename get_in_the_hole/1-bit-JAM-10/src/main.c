#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>

#include "core/app.h"
#include "render/render.h"

#include "types.h"
#include "utils.h"
#include "inputs.h"

int main(void)
{
    AppContext app;

    // Init
    if (!AppInit(&app))
        app.window.running = false;

    // Remember to fix this for web build
    while (app.window.running)
    {
        // Main loop
        // - Input
        // - Gamelogic
        // - Physics
        // - Copy to render (future proofing in case of threading)
        // - Render

        g_input = InputUpdate();

        RenderMain(&app.rc);

        if (WindowShouldClose())
            app.window.running = false;
    }

    // Cleanup
    AppCleanup(&app);
    return 0;
}
