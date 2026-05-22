#include "render.h"

#include <stdbool.h>

#include <raylib.h>

#include "types.h"
#include "inputs.h"

void RenderMain(RenderContext *rc)
{
    BeginTextureMode(rc->assets.textures.screen);
    {
        ClearBackground(BLACK);

        for (i32 y = 0; y < 100; y++)
        {
            for (i32 x = 0; x < 100; x++)
            {
                i32_2 g = (i32_2){ .x = x, .y = y };
                Color color = ((g.x + g.y) % 2) ? GREEN : BLACK;
                DrawRectangleV((Vector2){ x * 50, y * 50 }, (Vector2){ 50, 50 }, color);
            }
        }
    }
    EndTextureMode();

    BeginDrawing();
    {
        // If anything fails its purple
        ClearBackground(PURPLE);

        // Toggle shaders
        if (g_input.shaderActive)
        {
            BeginShaderMode(rc->assets.shaders.postprocess);
            {
                Size_f32 screenSize = (Size_f32){ .width = GetScreenWidth(), .height = GetScreenHeight() };
                SetShaderValue(rc->assets.shaders.postprocess, GetShaderLocation(rc->assets.shaders.postprocess, "screenSize"), &screenSize, SHADER_UNIFORM_VEC2);

                f32 time = GetTime();
                SetShaderValue(rc->assets.shaders.postprocess, GetShaderLocation(rc->assets.shaders.postprocess, "time"), &time, SHADER_UNIFORM_FLOAT);

                DrawTextureRec(rc->assets.textures.screen.texture, (Rectangle){ 0, 0, rc->assets.textures.screen.texture.width, -rc->assets.textures.screen.texture.height }, (Vector2){ 0, 0 }, WHITE);
            }
            EndShaderMode();
        }
        else 
            DrawTextureRec(rc->assets.textures.screen.texture, (Rectangle){ 0, 0, rc->assets.textures.screen.texture.width, -rc->assets.textures.screen.texture.height }, (Vector2){ 0, 0 }, WHITE);
    }
    EndDrawing();
}
