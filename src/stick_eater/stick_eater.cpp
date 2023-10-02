#include "stick_eater.hpp"

using namespace game;

StickEater::StickEater()
{
    m_velocity.x = 0;
    m_velocity.y = 0;

    m_speed = 80.0;
    p_behaviour.instantiate();
}

StickEater::~StickEater()
{
    p_behaviour.unref();
}

void StickEater::_ready()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_physics_process(false);
        return;
    }

    init_behaviour();

    Area2D *destroyer = static_cast<Area2D *>(get_node_or_null(p_path_destroyer));

    p_sprite = static_cast<AnimatedSprite2D *>(get_node_or_null(p_path_sprite));
    p_detector = static_cast<Area2D *>(get_node_or_null(p_path_detector));

    if (p_sprite == nullptr)
    {
        WARN_PRINT("StickEater: <sprite> is not assigned!");
    }

    if (p_behaviour == nullptr)
    {
        WARN_PRINT("StickEater: stick <detector> is not assigned!");
    }

    if (p_detector == nullptr)
    {
        WARN_PRINT("StickEater: <detector> is not assigned!");
    }

    if (destroyer == nullptr)
    {
        WARN_PRINT("StickEater: <destroyer> is not assigned!");
        return;
    }

    destroyer->connect("body_entered", Callable(this, "_process_eat"));
}

void StickEater::_physics_process(double delta)
{
    Ref<BehaviourContext> context = p_behaviour->get_context();

    Vector2 current_position = get_global_position();
    process_detector(current_position, context);

    p_behaviour->process(delta);

    Vector2 next_velocity = m_velocity;
    next_velocity = next_velocity.lerp(context->read_vector(KEY_NEXT_VELOCITY), 0.2f);

    m_velocity = next_velocity;
    set_velocity(m_speed * next_velocity);
    move_and_slide();

    context->write(KEY_ENTITY_POSITION, current_position);

    p_sprite->set_flip_h(next_velocity.x < 0);

    if (Math::abs(next_velocity.x) + Math::abs(next_velocity.y) < 0.1)
    {
        p_sprite->play("idle");
        return;
    }

    p_sprite->play("move");
}

void StickEater::process_detector(const Vector2 &current_position, Ref<BehaviourContext> &context)
{
    TypedArray<Node2D> candidates = p_detector->get_overlapping_bodies();

    Vector2 nearest_stick_position(100000, 100000);
    Vector2 nearest_obstacle_position(100000, 100000);
    float closest_stick_distance = FLT_MAX;
    float closest_obstacle_distance = FLT_MAX;

    for (int i = 0, l = candidates.size(); i < l; ++i)
    {
        Node2D *candidate = Object::cast_to<Node2D>(candidates[i]);

        check_nearest_stick(candidate, current_position, &nearest_stick_position, &closest_stick_distance);
        check_nearest_obstacle(candidate, current_position, &nearest_obstacle_position, &closest_obstacle_distance);
    }

    context->write(KEY_NEAREST_STICK_POSITION, nearest_stick_position);
    context->write(KEY_NEAREST_OBSTACLE_POSITION, nearest_obstacle_position);
}

void StickEater::check_nearest(const Vector2 &other_position, const Vector2 &self_position, Vector2 *position, float *min_distance)
{
    float distance = self_position.distance_squared_to(other_position);

    if (distance >= *min_distance)
        return;

    *min_distance = distance;
    *position = other_position;
}

void StickEater::check_nearest_stick(Node2D *node, const Vector2 &self_position, Vector2 *position, float *min_distance)
{
    if (!node->is_in_group(TAG_COLLECTABLE))
        return;

    check_nearest(node->get_global_position(), self_position, position, min_distance);
}

void StickEater::check_nearest_obstacle(Node2D *node, const Vector2 &self_position, Vector2 *position, float *min_distance)
{
    if (node->is_in_group(TAG_COLLECTABLE))
        return;

    check_nearest(node->get_global_position(), self_position, position, min_distance);
}

void StickEater::process_eat_stick(Node2D *candidate)
{
    if (!candidate->is_in_group(TAG_COLLECTABLE))
        return;

    candidate->queue_free();
}

void StickEater::set_speed(const double &speed)
{
    m_speed = speed;
}

double StickEater::get_speed() const
{
    return m_speed;
}

void StickEater::set_game_state(const Ref<GameState> &game_state)
{
    p_game_state = game_state;
}

Ref<GameState> StickEater::get_game_state() const
{
    return p_game_state;
}

void StickEater::set_sprite(const NodePath &path)
{
    p_path_sprite = path;
}

NodePath StickEater::get_sprite() const
{
    return p_path_sprite;
}

void StickEater::set_detector(const NodePath &path)
{
    p_path_detector = path;
}

NodePath StickEater::get_detector() const
{
    return p_path_detector;
}

void StickEater::set_destroyer(const NodePath &path)
{
    p_path_destroyer = path;
}

NodePath StickEater::get_destroyer() const
{
    return p_path_destroyer;
}

void StickEater::init_behaviour()
{
    Ref<SelectorNode> sel_actions;
    Ref<SequenceNode> seq_eat_stick;
    Ref<SequenceNode> seq_wander;
    Ref<IsNearStickNode> cond_near_stick;
    Ref<MoveTowardsNode> act_eat_stick;
    Ref<InvertNode> cond_not_near_stick;
    Ref<WanderNode> act_wander;

    sel_actions.instantiate();

    // Follow and eat stick action //
    seq_eat_stick.instantiate();
    cond_near_stick.instantiate();
    act_eat_stick.instantiate();

    seq_eat_stick->append(cond_near_stick);
    seq_eat_stick->append(act_eat_stick);

    // Wander action //
    seq_wander.instantiate();
    cond_not_near_stick.instantiate();
    act_wander.instantiate();

    cond_not_near_stick->set_target(cond_near_stick);

    seq_wander->append(cond_not_near_stick);
    seq_wander->append(act_wander);

    // Action Selector //
    sel_actions->append(seq_eat_stick);
    sel_actions->append(seq_wander);

    p_behaviour->set_root(sel_actions);
}

void StickEater::_bind_methods()
{
    StringName &class_name = StickEater::get_class_static();

    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &StickEater::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &StickEater::get_speed);

    ClassDB::bind_method(D_METHOD("set_game_state", "game_state"), &StickEater::set_game_state);
    ClassDB::bind_method(D_METHOD("get_game_state"), &StickEater::get_game_state);

    ClassDB::bind_method(D_METHOD("set_sprite", "path"), &StickEater::set_sprite);
    ClassDB::bind_method(D_METHOD("get_sprite"), &StickEater::get_sprite);

    ClassDB::bind_method(D_METHOD("set_detector", "detector"), &StickEater::set_detector);
    ClassDB::bind_method(D_METHOD("get_detector"), &StickEater::get_detector);

    ClassDB::bind_method(D_METHOD("set_destroyer", "path"), &StickEater::set_destroyer);
    ClassDB::bind_method(D_METHOD("get_destroyer"), &StickEater::get_destroyer);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::FLOAT, "speed"), "set_speed", "get_speed");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "game_state", PROPERTY_HINT_RESOURCE_TYPE, GameState::get_class_static()), "set_game_state", "get_game_state");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::NODE_PATH, "sprite", PROPERTY_HINT_NODE_PATH_VALID_TYPES, AnimatedSprite2D::get_class_static()), "set_sprite", "get_sprite");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::NODE_PATH, "detector", PROPERTY_HINT_NODE_PATH_VALID_TYPES, Area2D::get_class_static()), "set_detector", "get_detector");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::NODE_PATH, "destroyer", PROPERTY_HINT_NODE_PATH_VALID_TYPES, Area2D::get_class_static()), "set_destroyer", "get_destroyer");

    // Slots
    ClassDB::bind_method(D_METHOD("_process_eat", "other"), &StickEater::process_eat_stick);
}