#pragma once

#include <raylib.h>

// My Assets "class" :3
typedef struct Assets {
    struct {
        Shader postprocess;
    } shaders;

    struct {
        RenderTexture2D screen;
    } textures;

    struct {
        Font raylib;
        Font pressStart;
    } fonts;
} Assets;

bool AssetsInit(Assets *assets);
void AssetsCleanup(Assets *assets);
