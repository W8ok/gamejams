#pragma once

#include <raylib.h>

#include "../core/assets.h"

typedef struct RenderContext {
    Assets assets;
} RenderContext;

void RenderMain(RenderContext *rc);
