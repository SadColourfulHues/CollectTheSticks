#include "is_near_stick_node.hpp"
#include "stick_eater.hpp"

using namespace game;

BehaviourNodeResult IsNearStickNode::process(double delta, Ref<BehaviourContext> context)
{
    Vector2 entity_position = context->read_vector(KEY_ENTITY_POSITION);
    Vector2 stick_position = context->read_vector(KEY_NEAREST_STICK_POSITION);

    if (distance_between(entity_position, stick_position) > NEAR_STICK_DISTANCE_THRESHOLD)
        return PROCESS_FAIL;

    return PROCESS_SUCCESS;
}