#ifndef _PLAYER_CAMERA_H_
#define _PLAYER_CAMERA_H_

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    class PlayerCamera : public Camera2D
    {
        GDCLASS(PlayerCamera, Camera2D)

    public:
        PlayerCamera();
        ~PlayerCamera();

        void _ready() override;
        void _physics_process(double delta) override;

        void update_offset();
        void update_position(double fac);

        void set_subject(const NodePath &path);
        NodePath get_subject() const;

        void set_follow_fac(const double fac);
        double get_follow_fac() const;

    protected:
        static void _bind_methods();

    private:
        NodePath m_path_subject;
        Node2D *p_subject;

        Vector2 m_offset;
        double m_follow_fac;
    };
}

#endif
