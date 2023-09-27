#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include "macros.hpp"

/*
    Note to future me:
    Since we get to write this project in C++, we have a one-time
    excuse to do world bounds detection the old-school way.

    On bigger projects, use CharacterBody to
    have the player body respond properly to collisions.
*/
#define WORLD_WIDTH 128.5
#define WORLD_HEIGHT 123.5

namespace godot
{
    class PlayerController : public AnimatedSprite2D
    {
        GDCLASS(PlayerController, AnimatedSprite2D)

        private:
            Area2D *p_detector;

            Vector2 m_smooth_motion;
            double m_speed;

            void on_detector_entered(Node2D *other);

        protected:
            static void _bind_methods();

        public:
            PlayerController();
            ~PlayerController();

            void _ready();
            void _process(double delta);
            void _physics_process(double delta);

            void set_speed(const double speed);
            double get_speed() const;
    };
}

#endif