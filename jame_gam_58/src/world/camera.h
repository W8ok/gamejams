#pragma once

#include <raylib.h>

struct Entity;
void campera_update(Camera2D* cam, struct Entity* p, float dt);
void camera_init(Camera2D* cam, struct Entity* p);
