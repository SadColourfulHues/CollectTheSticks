#include "sequence_node.hpp"

using namespace behaviour;

BehaviourNodeResult SequenceNode::process(double delta, Ref<BehaviourContext> context)
{
    BehaviourNodeResult result;

    for (uint8_t i = 0; i < MAX_COMPOSITE_NODE_CHILDREN; ++i)
    {
        if (p_children[i].is_null())
            continue;

        result = p_children[i]->process(delta, context);

        if (result == PROCESS_SUCCESS)
            continue;

        return result;
    }

    return PROCESS_FAIL;
}