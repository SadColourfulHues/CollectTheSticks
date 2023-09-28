#ifndef _TREE_CONTROLLER_H_
#define _TREE_CONTROLLER_H_

#include <vector>

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/shape2d.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "tree_data.hpp"

#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16
#define SPRITE_HWIDTH 8
#define SPRITE_HHEIGHT 8
#define WORLD_SCALE 8

namespace godot
{
    class TreeController : public Node2D
    {
        GDCLASS(TreeController, Node2D)

    public:
        TreeController();
        ~TreeController();

        void _ready() override;

        void configure();
        void clear();

        void set_positions(const PackedVector2Array positions);
        PackedVector2Array get_positions() const;

        void set_spritesheet(const Ref<Texture2D> spritesheet);
        Ref<Texture2D> get_spritesheet() const;

        void set_material(const Ref<ShaderMaterial> material);
        Ref<ShaderMaterial> get_material() const;

        void set_offset(const float y);
        float get_offset() const;

        void set_seed(const int seed);
        int get_seed() const;

        void set_shape(const Ref<Shape2D> shape);
        Ref<Shape2D> get_shape() const;

        void set_collision_layer(const uint32_t mask);
        uint32_t get_collision_layer() const;

        void set_collision_mask(const uint32_t mask);
        uint32_t get_collision_mask() const;

    protected:
        static void _bind_methods();

    private:
        static Transform2D transform_for_position(const Vector2 &position);

        void configure_physics();
        void redraw();

        RandomNumberGenerator p_random;

        float m_y_offset;
        int m_random_seed;

        uint32_t m_collision_layer;
        uint32_t m_collision_mask;

        Ref<Texture2D> p_spritesheet;
        Ref<ShaderMaterial> p_material;
        Ref<Shape2D> p_shape;

        PackedVector2Array p_positions;
        std::vector<TreeData> p_data;
    };
}

#endif
