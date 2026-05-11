#include "world.h"

void world_init(World* w)
{
    *w = (World) {
        .map = {
            .size = {
                .x = 1000,
                .y = 1000,
            },
        },  
    };
}
