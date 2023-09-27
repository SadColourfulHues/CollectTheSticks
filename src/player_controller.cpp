#include "player_controller.hpp"
#include "collectable.hpp"

using namespace godot;


PlayerController::PlayerController()
{
    m_smooth_motion = Vector2(0, 0);
    m_speed = 80.0;
}

PlayerController::~PlayerController()
{
}

void PlayerController::_ready()
{
    p_detector = static_cast<Area2D *>(get_node_or_null("%Detector"));

    if (p_detector == nullptr)
    {
        WARN_PRINT("PlayerController: player must have a scene-unique Area2D child named 'Detector'.");
        return;
    }

    // Note to self: signal handlers must be registered to ClassDB to work
    p_detector->connect("body_entered", Callable(this, "area_body_entered"));
}

void PlayerController::_process(double delta)
{
    // Without this, the node will spam InputMap warnings in the debug console
    // https://github.com/godotengine/godot/issues/74993#issuecomment-1582078412
    NO_EDITOR

    Input *input = Input::get_singleton();

    Vector2 input_vec = input->get_vector("left", "right", "up", "down");
    Vector2 next_motion = Vector2(0, 0);

    if (input_vec.length_squared() >= 0.1)
    {
        play("walk");
        next_motion = input_vec;
    }
    else
    {
        play("idle");
    }

    m_smooth_motion = m_smooth_motion.lerp(next_motion, 0.1);
    set_flip_h(m_smooth_motion.x < 0.0);
}

void PlayerController::_physics_process(double delta)
{
    Vector2 position = get_position();
    position += m_smooth_motion * (m_speed * delta);

    position.x = CLAMP(position.x, -WORLD_WIDTH, WORLD_WIDTH);
    position.y = CLAMP(position.y, -WORLD_HEIGHT, WORLD_HEIGHT);

    set_position(position);
}

void PlayerController::on_detector_entered(Node2D *other)
{
    if (!other->is_in_group(TAG_COLLECTABLE))
        return;

    Collectable *collectable = static_cast<Collectable *>(other);
    collectable->collect();
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
    StringName &class_name = PlayerController::get_class_static();

    ClassDB::bind_method(D_METHOD("get_speed"), &PlayerController::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &PlayerController::set_speed);

    ClassDB::add_property(class_name, PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

    // Slots
    ClassDB::bind_method(D_METHOD("area_body_entered"), &PlayerController::on_detector_entered);
}