#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include "macros.hpp"

namespace godot
{
    class PlayerController : public Sprite2D
    {
        GDCLASS(PlayerController, Sprite2D)

        private:
            Vector2 m_smooth_motion;
            double m_speed;

        protected:
            static void _bind_methods();

        public:
            PlayerController();
            ~PlayerController();

            void _process(double delta);
            void _physics_process(double delta);

            void set_speed(const double speed);
            double get_speed() const;
    };
}

#endif