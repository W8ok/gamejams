#pragma once

#include <raylib.h>

struct EntityList;
struct Entity;
void spawn_fat_skeleton(struct EntityList* list, Vector2 pos);
void ai_fat_skeleton(struct Entity* skeleton, struct Entity* player, float dt);
