#include "wander_node.hpp"
#include "stick_eater.hpp"

using namespace game;

WanderNode::WanderNode()
{
    p_random.randomize();
}

WanderNode::~WanderNode()
{
}

#include <godot_cpp/variant/utility_functions.hpp>

BehaviourNodeResult WanderNode::process(double delta, Ref<BehaviourContext> context)
{
    float f_delta = static_cast<float>(delta);

    Vector2 position = context->read_vector(KEY_ENTITY_POSITION);
    Vector2 obstacle_position = context->read_vector(KEY_NEAREST_OBSTACLE_POSITION);
    Vector2 target_dir = context->read_vector(KEY_WANDER_DIR);

    Vector2 travel_delta = position - context->read_vector(KEY_WANDER_LAST_POSITION);
    Vector2 random_dir(-1.0 + 2.0 * p_random.randf(), -1.0 + 2.0 * p_random.randf());

    target_dir.x = Math::move_toward(target_dir.x, Math::abs(travel_delta.x) <= 0.2f ? -target_dir.x - random_dir.x * 0.33f : random_dir.x, 5.0f * f_delta);
    target_dir.y = Math::move_toward(target_dir.y, Math::abs(travel_delta.y) <= 0.2f ? -target_dir.y - random_dir.y * 0.33f : random_dir.y, 5.0f * f_delta);

    context->write(KEY_WANDER_DIR, target_dir);
    target_dir.normalize();

    if (distance_between(position, obstacle_position) <= WANDER_AVOID_OBSTACLE_DISTANCE)
    {
        float dfac = 1.0f - CLAMP((position.distance_squared_to(obstacle_position) / WANDER_AVOID_OBSTACLE_DISTANCE), 0.0f, 1.0f);
        target_dir += (position - obstacle_position) * dfac;
    }

    context->write(KEY_NEXT_VELOCITY, target_dir);
    context->write(KEY_WANDER_LAST_POSITION, context->read_vector(KEY_WANDER_LAST_POSITION).lerp(position, 0.1f));

    return PROCESS_RUNNING;
}