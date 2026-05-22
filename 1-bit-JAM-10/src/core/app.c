#include "app.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#include "inputs.h"
#include "types.h"

bool AppInit(AppContext *app)
{
    // Not needed in C23 but... idk i wanted to
    memset(app, 0, sizeof(AppContext));

    *app = (AppContext){
        .window = {
            .name = "temp",
            .size = {
                .width = 800,
                .height = 600,
            },
            .fps = 60,
            .running = true,
        },
    };

    InitWindow(app->window.size.width, app->window.size.height, app->window.name);
    SetTargetFPS(app->window.fps);

    if (!AssetsInit(&app->rc.assets))
        return false;

    return true;
}

void AppCleanup(AppContext *app)
{
    AssetsCleanup(&app->rc.assets);
    CloseWindow();
}
