#pragma once

#include <stdbool.h>

#include "../render/render.h"

#include "types.h"
#include "inputs.h"

typedef struct AppContext {
    struct {
        const char *name;
        Size_i32 size;
        i32 fps;
        bool running;
    } window;

    RenderContext rc;
} AppContext;

bool AppInit(AppContext *app);
void AppCleanup(AppContext *app);

InputState InputUpdate(void);
