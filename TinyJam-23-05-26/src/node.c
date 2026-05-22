#include "node.h"
#include "utils.h"

void node_main(Nodes* nodes)
{ 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Node node = (Node){
            .pos = GetMousePosition(),
            .radius = 100,
        };
        DA_APPEND(nodes, node);
    }
}
