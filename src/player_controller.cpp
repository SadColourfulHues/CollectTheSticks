#include "player_controller.hpp"

using namespace godot;


PlayerController::PlayerController()
{
    m_smooth_motion = Vector2(0, 0);
    m_speed = 80.0;
}

PlayerController::~PlayerController()
{
}

void PlayerController::_process(double delta)
{
    NO_EDITOR

    Vector2 next_motion = Vector2(0, 0);

    Vector2 input_vec = Input::get_singleton()->
        get_vector("left", "right", "up", "down");

    if (input_vec.length_squared() >= 0.1)
    {
        next_motion = input_vec;
    }

    m_smooth_motion = m_smooth_motion.lerp(next_motion, 0.1);
}

void PlayerController::_physics_process(double delta)
{
    Vector2 position = get_position();
    position += m_smooth_motion * (m_speed * delta);

    set_position(position);
}

void PlayerController::set_speed(const double speed)
{
    m_speed = speed;
}

double PlayerController::get_speed() const
{
    return m_speed;
}

void PlayerController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_speed"), &PlayerController::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &PlayerController::set_speed);

    ClassDB::add_property(
        "PlayerController", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}