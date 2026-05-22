#pragma once

#include <raylib.h>
#include <stdlib.h>

typedef struct Node {
    Vector2 pos;
    float radius;
} Node;

typedef struct Nodes {
    Node* data;
    size_t capacity;
    size_t count;
} Nodes;

void node_main(Nodes* nodes);
