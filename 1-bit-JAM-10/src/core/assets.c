#include "assets.h"
#include <stdbool.h>

bool AssetsInit(Assets *assets)
{

#ifdef PLATFORM_WEB
    #define ASSETS_PATH "/assets/"
#else
    #define ASSETS_PATH "assets/"
#endif

#define SHADER_PATH     ASSETS_PATH "shaders/"
#define TEXTURE_PATH    ASSETS_PATH "textures/"
#define FONT_PATH       ASSETS_PATH "fonts/"
    {
        // Shaders
        assets->shaders.postprocess = LoadShader(SHADER_PATH "postprocess.vert", SHADER_PATH "postprocess.frag");
        if (!IsShaderValid(assets->shaders.postprocess))
            return false;


        // Textures
        assets->textures.screen = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        if (!IsRenderTextureValid(assets->textures.screen))
            return false;


        // Fonts
        assets->fonts.raylib = GetFontDefault();
        if (!IsFontValid(assets->fonts.raylib))
            return false;

        assets->fonts.pressStart = LoadFont(FONT_PATH "PressStart2P-vaV7.ttf");
        if (!IsFontValid(assets->fonts.pressStart))
            return false;
    }
#undef ASSETS_PATH
#undef SHADER_PATH
#undef TEXTURE_PATH
#undef FONT_PATH

    return true;
}

void AssetsCleanup(Assets *assets)
{
    // Shaders
    UnloadShader(assets->shaders.postprocess);

    // Textures
    UnloadRenderTexture(assets->textures.screen);

    //Fonts
    UnloadFont(assets->fonts.raylib);
    UnloadFont(assets->fonts.pressStart);
}
