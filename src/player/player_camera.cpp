#include "player_camera.hpp"

using namespace game;

PlayerCamera::PlayerCamera()
{
    m_path_subject = NodePath();

    p_subject = nullptr;
    m_follow_fac = 0.125;
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::_ready()
{
    if (m_path_subject.is_empty())
    {
        WARN_PRINT("PlayerCamera: no <subject> were provided!");
    }

    p_subject = static_cast<Node2D *>(get_node_or_null(m_path_subject));
    update_offset();
}

void PlayerCamera::_physics_process(double delta)
{
    update_position(m_follow_fac);
}

void PlayerCamera::update_offset()
{
    if (p_subject == nullptr)
        return;

    m_offset = p_subject->get_position() - get_position();
}

void PlayerCamera::update_position(double fac)
{
    if (p_subject == nullptr)
        return;

    Vector2 position = get_position();
    Vector2 next_position = p_subject->get_position() + m_offset;

    position += (next_position - position) * fac;
    set_position(position);
}

void PlayerCamera::set_subject(const NodePath &path)
{
    m_path_subject = path;
}

NodePath PlayerCamera::get_subject() const
{
    return m_path_subject;
}

void PlayerCamera::set_follow_fac(const double fac)
{
    m_follow_fac = fac;
}

double PlayerCamera::get_follow_fac() const
{
    return m_follow_fac;
}

void PlayerCamera::_bind_methods()
{
    StringName &class_name = PlayerCamera::get_class_static();

    ClassDB::bind_method(D_METHOD("get_subject"), &PlayerCamera::get_subject);
    ClassDB::bind_method(D_METHOD("set_subject", "p_subject"), &PlayerCamera::set_subject);

    ClassDB::bind_method(D_METHOD("get_follow_fac"), &PlayerCamera::get_follow_fac);
    ClassDB::bind_method(D_METHOD("set_follow_fac", "p_follow_Fac"), &PlayerCamera::set_follow_fac);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::NODE_PATH, "subject"), "set_subject", "get_subject");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::FLOAT, "follow_fac"), "set_follow_fac", "get_follow_fac");
}