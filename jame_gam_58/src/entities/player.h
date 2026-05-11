#pragma once

#include <raylib.h>
#include "needle.h"

struct Entities;
void spawn_player(struct Entities* e, NeedleList* needles);
struct Entity;
void player_control(struct Entity* p, Needle* n, float dt);
