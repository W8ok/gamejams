#pragma once

#include "collisions.h"
#include "player.h"
#include "dummy.h"
#include "needle.h"
#include "smol_skeleton.h"

#include "../world/map.h"

#include <stdlib.h>
#include <stdbool.h>


typedef enum {
    ENTITY_NONE = 0,
    ENTITY_PLAYER,
    ENTITY_TRAINING_DUMMY,
    ENTITY_SMOL_SKELETON,
} EntityType;

typedef struct Entity {
    EntityType type;
    
    Vector2 pos;
    Vector2 vel;
    int health;
    bool active;
    bool needle_inside;

    int needle_id;
    bool has_needle;

    struct {
        Vector2 offset;
        float mass;
        float radius;
    } hitbox;

    Vector2 animation_state;
} Entity;

typedef struct EntityList {
    Entity* data;
    size_t capacity;
    size_t count;
} EntityList;

typedef struct Textures {
    Texture2D player;
} Textures;

typedef struct Entities {
    EntityList all;
    NeedleList needles;
    size_t player_idx;
    Textures tex;
    Map* map;
} Entities;

void entity_init(Entities* e);
void entity_update(Entities* e, float dt);
void entity_render(Entities* e, float dt);
