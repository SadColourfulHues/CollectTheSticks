#include "invert_node.hpp"

using namespace behaviour;

BehaviourNodeResult InvertNode::process(double delta, Ref<BehaviourContext> context)
{
    BehaviourNodeResult result = p_target->process(delta, context);

    if (result == PROCESS_RUNNING)
        return result;

    return (result == PROCESS_FAIL ? PROCESS_SUCCESS : result);
}