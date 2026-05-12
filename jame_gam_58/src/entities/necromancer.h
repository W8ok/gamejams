#pragma once

#include <raylib.h>

struct Entity;
struct EntityList;
void ai_necromancer(struct Entity* e, struct Entity* player, float dt, struct EntityList* list);
void spawn_necromancer(struct EntityList* list, Vector2 pos);
