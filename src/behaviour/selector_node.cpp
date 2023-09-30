#include "selector_node.hpp"

using namespace godot;

BehaviourNodeResult SelectorNode::process(double delta)
{
    BehaviourNodeResult result;

    for (uint8_t i = 0; i < MAX_COMPOSITE_NODE_CHILDREN; ++i)
    {
        if (p_children[i].is_null())
            continue;

        result = p_children[i]->process(delta);

        if (result == PROCESS_FAIL)
            continue;

        return result;
    }

    return PROCESS_FAIL;
}