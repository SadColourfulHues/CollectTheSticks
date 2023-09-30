#include "player_controller.hpp"
#include "collectable/collectable.hpp"

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
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_process(false);
        set_process_internal(false);
        set_physics_process(false);
        set_physics_process_internal(false);

        return;
    }

    p_sprite = static_cast<AnimatedSprite2D *>(get_node_or_null("%Sprite"));
    p_detector = static_cast<Area2D *>(get_node_or_null("%Detector"));

    if (p_sprite == nullptr)
    {
        ERR_PRINT("PlayerController: player must have scene-unique AnimatedSprite2D child named 'Sprite'.");
        return;
    }

    if (p_detector == nullptr)
    {
        ERR_PRINT("PlayerController: player must have a scene-unique Area2D child named 'Detector'.");
        return;
    }

    // Note to self: signal handlers must be registered to ClassDB to work
    p_detector->connect("body_entered", Callable(this, "area_body_entered"));
}

void PlayerController::_process(double)
{
    Input *input = Input::get_singleton();

    Vector2 input_vec = input->get_vector("left", "right", "up", "down");
    Vector2 next_motion = Vector2(0, 0);

    if (input_vec.length_squared() >= 0.1)
    {
        p_sprite->play("walk");
        next_motion = input_vec;
    }
    else
    {
        p_sprite->play("idle");
    }

    m_smooth_motion = m_smooth_motion.lerp(next_motion, 0.1);
    p_sprite->set_flip_h(m_smooth_motion.x < 0.0);
}

void PlayerController::_physics_process(double)
{
    set_velocity(m_smooth_motion * m_speed);
    move_and_slide();
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
