#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot
{
    class PlayerController final : public CharacterBody2D
    {
        GDCLASS(PlayerController, CharacterBody2D)

    public:
        PlayerController();
        ~PlayerController();

        void _ready() override;
        void _process(double) override;
        void _physics_process(double) override;

        void set_speed(const double speed);
        double get_speed() const;

    protected:
        static void _bind_methods();

    private:
        AnimatedSprite2D *p_sprite;
        Area2D *p_detector;

        Vector2 m_smooth_motion;
        double m_speed;

        void on_detector_entered(Node2D *other);
    };
}

#endif
