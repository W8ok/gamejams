#pragma once

#include <stdbool.h>

typedef struct InputState {
    bool up, down, left, right;
    bool jump, interract;
    bool mainAction, secondaryAction;
    bool shaderActive;
} InputState;

extern InputState g_input;
