#pragma once

struct EntityList;
struct Entity;
struct Needle;

void collide_needle_entity(struct Entity* e, struct Needle* needle);
void entity_inter_collision(struct EntityList* list);
