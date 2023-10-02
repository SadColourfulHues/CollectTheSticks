#ifndef _STICK_EATER_H_
#define _STICK_EATER_H_

#include <float.h>

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "behaviour/sequence_node.hpp"
#include "behaviour/selector_node.hpp"
#include "behaviour/invert_node.hpp"

#include "collectable/collectable.hpp"
#include "behaviour/behaviour_tree.hpp"
#include "core/game_state.hpp"

#include "is_near_stick_node.hpp"
#include "move_towards_node.hpp"
#include "wander_node.hpp"

#define KEY_NEAREST_STICK_POSITION "sps"
#define KEY_NEAREST_OBSTACLE_POSITION "ops"
#define KEY_ENTITY_POSITION "ps"
#define KEY_NEXT_VELOCITY "nv"

using namespace behaviour;
using namespace godot;

namespace game
{
    class StickEater final : public CharacterBody2D
    {
        GDCLASS(StickEater, CharacterBody2D);

    public:
        StickEater();
        ~StickEater();

        void _ready() override;
        void _physics_process(double delta) override;

        void set_speed(const double &speed);
        double get_speed() const;

        void set_game_state(const Ref<GameState> &game_state);
        Ref<GameState> get_game_state() const;

        void set_sprite(const NodePath &path);
        NodePath get_sprite() const;

        void set_detector(const NodePath &path);
        NodePath get_detector() const;

        void set_destroyer(const NodePath &path);
        NodePath get_destroyer() const;

    private:
        static void _bind_methods();

        void process_detector(const Vector2 &current_position, Ref<BehaviourContext> &context);
        void process_eat_stick(Node2D *candidate);

        void check_nearest(const Vector2 &other_position, const Vector2 &self_position, Vector2 *position, float *min_distance);
        void check_nearest_stick(Node2D *node, const Vector2 &self_position, Vector2 *position, float *min_distance);
        void check_nearest_obstacle(Node2D *node,const Vector2 &self_position, Vector2 *position, float *min_distance);

        void init_behaviour();

        Ref<BehaviourTree> p_behaviour;

        NodePath p_path_sprite;
        NodePath p_path_detector;
        NodePath p_path_destroyer;

        Ref<GameState> p_game_state;

        Area2D *p_detector;
        AnimatedSprite2D *p_sprite;

        Vector2 m_velocity;
        double m_speed;
    };
};

#endif