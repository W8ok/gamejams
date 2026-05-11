#include "map.h"

void map_render(Map* map)
{
    Rectangle map_rect = {
        .x = -map->size.x / 2,
        .y = -map->size.y / 2,
        .width = map->size.x,
        .height = map->size.y,
    };

    DrawRectangleLinesEx(map_rect, 4, RED);
}
