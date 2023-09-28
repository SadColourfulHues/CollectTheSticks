#include "tree_controller.hpp"

using namespace godot;

TreeController::TreeController()
{
    m_random_seed = 0;
    m_y_offset = -24;

    m_collision_layer = 1;
    m_collision_mask = 1;

    set_y_sort_enabled(true);
}

TreeController::~TreeController()
{
    clear();
}

void TreeController::_ready()
{
    call_deferred("__configure_visuals");
    call_deferred("__configure_physics");
}

void TreeController::clear()
{
    RenderingServer *render_server = RenderingServer::get_singleton();
    PhysicsServer2D *physics_server = PhysicsServer2D::get_singleton();

    for (int i = 0, l = p_data.size(); i < l; ++i)
    {
        // Canvas Item
        if (!p_data[i].visual_rid.is_valid())
            continue;

        render_server->free_rid(p_data[i].visual_rid);

        // Static body
        if (!p_data[i].body_rid.is_valid())
            continue;

        physics_server->free_rid(p_data[i].body_rid);
    }

    p_data.clear();
}

void TreeController::configure()
{
    RenderingServer *render_server = RenderingServer::get_singleton();
    clear();

    p_random.set_seed(m_random_seed);

    Rect2 src_rect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
    Rect2 dst_rect(0, m_y_offset, SPRITE_WIDTH, SPRITE_HEIGHT);

    RID parent_rid = this->get_canvas_item();
    RID texture_rid = p_spritesheet->get_rid();
    RID material_rid;

    if (p_material.is_valid())
    {
        material_rid = p_material->get_rid();
    }

    // Initialise
    for (int i = 0, l = p_positions.size(); i < l; ++i)
    {
        Transform2D transform = TreeController::transform_for_position(p_positions[i]);
        TreeData data;

        uint8_t index = p_random.randi() % 5;
        src_rect.set_position(Vector2(SPRITE_WIDTH * index, 0));

        data.position = p_positions[i];
        data.visual_rid = render_server->canvas_item_create();

        render_server->canvas_item_set_parent(data.visual_rid, parent_rid);
        render_server->canvas_item_set_transform(data.visual_rid, transform);
        render_server->canvas_item_set_material(data.visual_rid, material_rid);

        render_server->canvas_item_set_default_texture_filter(data.visual_rid,
            RenderingServer::CanvasItemTextureFilter::CANVAS_ITEM_TEXTURE_FILTER_NEAREST);

        render_server->canvas_item_add_texture_rect_region(data.visual_rid, dst_rect, texture_rid, src_rect);

        p_data.push_back(data);
    }
}

void TreeController::configure_physics()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        if (!p_shape.is_valid())
        {
            WARN_PRINT("TreeController: no collision <shape> were provided!");
        }

        return;
    }

    RID shape_rid = p_shape->get_rid();
    RID space_rid = get_world_2d()->get_space();

    PhysicsServer2D *physics_server = PhysicsServer2D::get_singleton();
    Vector2 global_position = get_global_position();

    for (int i = 0, l = p_data.size(); i < l; ++i)
    {
        if (!p_data[i].visual_rid.is_valid())
            continue;

        Transform2D transform = TreeController::transform_for_position(p_data[i].position);
        Vector2 offset = transform.get_origin();

        offset.x = global_position.x + WORLD_SCALE * (offset.x + SPRITE_WIDTH);
        offset.y = global_position.y + WORLD_SCALE * (offset.y - 10.8 + SPRITE_HEIGHT + m_y_offset);

        transform.set_origin(offset);
        p_data[i].body_rid = physics_server->body_create();

        physics_server->body_set_space(p_data[i].body_rid, space_rid);
        physics_server->body_add_shape(p_data[i].body_rid, shape_rid);
        physics_server->body_set_mode(p_data[i].body_rid, PhysicsServer2D::BodyMode::BODY_MODE_STATIC);
        physics_server->body_set_state(p_data[i].body_rid, PhysicsServer2D::BodyState::BODY_STATE_TRANSFORM, transform);
    }
}

void TreeController::redraw()
{
    if (p_spritesheet.is_null())
        return;

    RenderingServer *render_server = RenderingServer::get_singleton();
    p_random.set_seed(m_random_seed);

    Rect2 src_rect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
    Rect2 dst_rect(0, m_y_offset, SPRITE_WIDTH, SPRITE_HEIGHT);

    RID texture_rid = p_spritesheet->get_rid();

    for (int i = 0, l = p_data.size(); i < l; ++i)
    {
        if (!p_data[i].visual_rid.is_valid())
            continue;

        uint8_t index = p_random.randi() % 5;
        src_rect.set_position(Vector2(SPRITE_WIDTH * index, 0));

        Transform2D transform = TreeController::transform_for_position(p_data[i].position);

        render_server->canvas_item_clear(p_data[i].visual_rid);
        render_server->canvas_item_add_texture_rect_region(p_data[i].visual_rid, dst_rect, texture_rid, src_rect);
        render_server->canvas_item_set_transform(p_data[i].visual_rid, transform);
    }
}

void TreeController::set_positions(const PackedVector2Array positions)
{
    if (positions.is_empty() || positions == p_positions)
        return;

    p_positions = positions;

    // Note to future self: this may be a bit inefficient, but it'll do for now
    configure();
}

PackedVector2Array TreeController::get_positions() const
{
    return p_positions;
}

void TreeController::set_spritesheet(const Ref<Texture2D> spritesheet)
{
    if (spritesheet.is_null())
        return;

    p_spritesheet = spritesheet;
    redraw();
}

Ref<Texture2D> TreeController::get_spritesheet() const
{
    return p_spritesheet;
}

void TreeController::set_material(const Ref<ShaderMaterial> material)
{
    if (material.is_null())
        return;

    p_material = material;
    redraw();
}

Ref<ShaderMaterial> TreeController::get_material() const
{
    return p_material;
}

void TreeController::set_offset(const float offset)
{
    m_y_offset = offset;
    redraw();
}

float TreeController::get_offset() const
{
    return m_y_offset;
}

void TreeController::set_seed(const int seed)
{
    m_random_seed = seed;
    redraw();
}

int TreeController::get_seed() const
{
    return m_random_seed;
}

void TreeController::set_shape(const Ref<Shape2D> shape)
{
    p_shape = shape;
}


Ref<Shape2D> TreeController::get_shape() const
{
    return p_shape;
}

void TreeController::set_collision_layer(const uint32_t mask)
{
    m_collision_layer = mask;
}

uint32_t TreeController::get_collision_layer() const
{
    return m_collision_layer;
}

void TreeController::set_collision_mask(const uint32_t mask)
{
    m_collision_mask = mask;
}

uint32_t TreeController::get_collision_mask() const
{
    return m_collision_mask;
}

Transform2D TreeController::transform_for_position(const Vector2 &position)
{
    Transform2D transform;
    transform.set_origin(position);
    transform.scale(Size2(2.0, 2.0));

    return transform;
}

void TreeController::_bind_methods()
{
    StringName &class_name = TreeController::get_class_static();

    ClassDB::bind_method(D_METHOD("__configure_physics"), &TreeController::configure_physics);
    ClassDB::bind_method(D_METHOD("__configure_visuals"), &TreeController::configure);

    ClassDB::bind_method(D_METHOD("set_spritesheet", "p_spritesheet"), &TreeController::set_spritesheet);
    ClassDB::bind_method(D_METHOD("get_spritesheet"), &TreeController::get_spritesheet);

    ClassDB::bind_method(D_METHOD("set_positions", "p_positions"), &TreeController::set_positions);
    ClassDB::bind_method(D_METHOD("get_positions"), &TreeController::get_positions);

    ClassDB::bind_method(D_METHOD("set_material", "p_material"), &TreeController::set_material);
    ClassDB::bind_method(D_METHOD("get_material"), &TreeController::get_material);

    ClassDB::bind_method(D_METHOD("set_y_offset", "m_offset"), &TreeController::set_offset);
    ClassDB::bind_method(D_METHOD("get_y_offset"), &TreeController::get_offset);

    ClassDB::bind_method(D_METHOD("set_seed", "m_seed"), &TreeController::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"), &TreeController::get_seed);

    ClassDB::bind_method(D_METHOD("set_shape", "p_shape"), &TreeController::set_shape);
    ClassDB::bind_method(D_METHOD("get_shape"), &TreeController::get_shape);

    ClassDB::bind_method(D_METHOD("set_collision_layer", "m_collision_layer"), &TreeController::set_collision_layer);
    ClassDB::bind_method(D_METHOD("get_collision_layer"), &TreeController::get_collision_layer);

    ClassDB::bind_method(D_METHOD("set_collision_mask", "m_collision_mask"), &TreeController::set_collision_mask);
    ClassDB::bind_method(D_METHOD("get_collision_mask"), &TreeController::get_collision_mask);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::INT, "seed"), "set_seed", "get_seed");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::FLOAT, "y_offset"), "set_y_offset", "get_y_offset");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "shape", PROPERTY_HINT_RESOURCE_TYPE, Shape2D::get_class_static()), "set_shape", "get_shape");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "spritesheet", PROPERTY_HINT_RESOURCE_TYPE, Texture2D::get_class_static()), "set_spritesheet", "get_spritesheet");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, ShaderMaterial::get_class_static()), "set_material", "get_material");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::INT, "collision_layer", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_collision_layer", "get_collision_layer");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::INT, "collision_mask", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_collision_mask", "get_collision_mask");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::ARRAY, "positions", PROPERTY_HINT_ARRAY_TYPE, "Vector2"), "set_positions", "get_positions");
}

