#ifndef _PLAYER_CAMERA_H_
#define _PLAYER_CAMERA_H_

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    class PlayerCamera : public Camera2D
    {
        GDCLASS(PlayerCamera, Camera2D)

        private:
            NodePath m_path_subject;
            Node2D *p_subject;

            Vector2 m_offset;
            double m_follow_fac;

        protected:
            static void _bind_methods();

        public:
            PlayerCamera();
            ~PlayerCamera();

            void _ready();
            void _physics_process(double delta);

            void update_offset();
            void update_position(double fac);

            void set_subject(const NodePath &path);
            NodePath get_subject() const;

            void set_follow_fac(const double fac);
            double get_follow_fac() const;
    };
}

#endif