#pragma once

#include <raylib.h>

struct EntityList;
struct Entity;
void spawn_fast_skeleton(struct EntityList* list, Vector2 pos);
void ai_fast_skeleton(struct Entity* skeleton, struct Entity* player, float dt);
