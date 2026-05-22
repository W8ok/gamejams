#include "app.h"

InputState g_input;

InputState InputUpdate(void)
{
    static bool shaderActive = true;
    if (IsKeyPressed(KEY_F1))
        shaderActive = !shaderActive;

    return (InputState){
        .up     = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP),
        .down   = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN),
        .left   = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT),
        .right  = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT),

        .jump       = IsKeyDown(KEY_SPACE),
        .interract  = IsKeyDown(KEY_E),

        .mainAction      = IsMouseButtonDown(MOUSE_BUTTON_LEFT),
        .secondaryAction = IsMouseButtonDown(MOUSE_BUTTON_RIGHT),

        .shaderActive = shaderActive,
    };
}
