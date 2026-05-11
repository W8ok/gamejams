#pragma once

#include <raylib.h>
#include <stdlib.h>

typedef enum NeedleType {
    NEEDLE_NONE,
    NEEDLE_SHORT,
    NEEDLE_LONG,
} NeedleType;

typedef struct Needle {
    int parent_idx;
    bool active;

    NeedleType type;

    Vector2 start;
    Vector2 end;
    Vector2 dir;

    float thickness;
} Needle;

typedef struct NeedleList {
    Needle* data;
    size_t count;
    size_t capacity;
} NeedleList;

void spawn_needle(NeedleList* needles, Needle needle);
void needle_render(NeedleList* needles);

struct Entity;
void needle_update(struct Entity* player, struct Entity* e, NeedleList* needles);
