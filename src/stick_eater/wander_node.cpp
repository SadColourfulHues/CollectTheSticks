#include <godot_cpp/variant/utility_functions.hpp>

#include "wander_node.hpp"
#include "stick_eater.hpp"

using namespace game;

WanderNode::WanderNode()
{
    p_random.randomize();
    m_update_wander_tick = 0.0f;
}

WanderNode::~WanderNode()
{
}

BehaviourNodeResult WanderNode::process(double delta, Ref<BehaviourContext> context)
{
    Vector2 last_position = context->read_vector(KEY_WANDER_LAST_POSITION);
    Vector2 position = context->read_vector(KEY_ENTITY_POSITION);
    Vector2 target_dir = context->read_vector(KEY_WANDER_TARGET_DIR);

    float f_delta = static_cast<float>(delta);

    m_update_wander_tick -= f_delta;

    if (m_update_wander_tick <= 0.0)
    {
        Vector2 old_dir = target_dir;

        target_dir.x = -1.0 + 2.0 * p_random.randf();
        target_dir.y = -1.0 + 2.0 * p_random.randf();

        Vector2 travel_delta = (position - last_position).abs();

        if (travel_delta.x < 0.1f && Math::sign(old_dir.x) == Math::sign(target_dir.x))
        {
            target_dir.x *= -1.0f;
        }

        if (travel_delta.y < 0.1f && Math::sign(old_dir.y) == Math::sign(target_dir.y))
        {
            target_dir.y *= -1.0f;
        }

        target_dir.normalize();

        context->write(KEY_WANDER_TARGET_DIR, target_dir);
        m_update_wander_tick = p_random.randf_range(1.0, 2.8);
    }

    Vector2 obstacle_position = context->read_vector(KEY_NEAREST_OBSTACLE_POSITION);
    Vector2 dir = context->read_vector(KEY_WANDER_DIR);

    dir = dir.move_toward(target_dir, 2.0f * f_delta);
    context->write(KEY_WANDER_DIR, dir);

    if (distance_between(position, obstacle_position) <= WANDER_AVOID_OBSTACLE_DISTANCE)
    {
        dir += (position - obstacle_position).normalized() * 1.5f;
        dir.normalize();
    }

    context->write(KEY_NEXT_VELOCITY, dir);
    context->write(KEY_WANDER_LAST_POSITION, position);

    return PROCESS_RUNNING;
}