#include "move_towards_node.hpp"
#include "stick_eater.hpp"

using namespace game;

BehaviourNodeResult MoveTowardsNode::process(double delta, Ref<BehaviourContext> context)
{
    Vector2 position = context->read_vector(KEY_ENTITY_POSITION);
    Vector2 stick_position = context->read_vector(KEY_NEAREST_STICK_POSITION);
    Vector2 obstacle_position = context->read_vector(KEY_NEAREST_OBSTACLE_POSITION);

    Vector2 target_dir = (stick_position - position).normalized();

    if (distance_between(position, obstacle_position) <= MOVE_AVOID_OBSTACLE_DISTANCE)
    {
        float dfac = 1.0f - CLAMP((position.distance_squared_to(obstacle_position) / MOVE_AVOID_OBSTACLE_DISTANCE), 0.0f, 1.0f);
        target_dir += (position - obstacle_position) * dfac;
    }

    context->write(KEY_NEXT_VELOCITY, target_dir);
    return PROCESS_RUNNING;
}