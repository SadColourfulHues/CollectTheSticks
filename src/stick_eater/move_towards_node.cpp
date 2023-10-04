#include "move_towards_node.hpp"
#include "stick_eater.hpp"

using namespace game;

BehaviourNodeResult MoveTowardsNode::process(double delta, Ref<BehaviourContext> context)
{
    Vector2 position = context->read_vector(KEY_ENTITY_POSITION);
    Vector2 stick_position = context->read_vector(KEY_NEAREST_STICK_POSITION);

    Vector2 target_dir = (stick_position - position).normalized();

    context->write(KEY_NEXT_VELOCITY, target_dir);
    return PROCESS_RUNNING;
}