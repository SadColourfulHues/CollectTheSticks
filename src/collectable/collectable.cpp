#include "collectable.hpp"

using namespace game;

Collectable::Collectable()
{
    m_score_value = 1;
    add_to_group(TAG_COLLECTABLE);
}

Collectable::~Collectable()
{
}

void Collectable::collect()
{
    if (p_game_state.is_null())
    {
        ERR_PRINT("Collectable: <game state> was not assigned!");
        return;
    }

    p_game_state->add_score(m_score_value);
    emit_signal("on_collected");

    queue_free();

    if (p_collect_sound_effect.is_null())
        return;

    p_game_state->audio_play(p_collect_sound_effect, get_global_position(), 1.0f, 500.0f, BUS_SFX);
}

void Collectable::set_game_state(const Ref<GameState> &state)
{
    p_game_state = state;
}

Ref<GameState> Collectable::get_game_state() const
{
    return p_game_state;
}

void Collectable::set_score_value(const uint32_t value)
{
    m_score_value = value;
}

uint32_t Collectable::get_score_value() const
{
    return m_score_value;
}

void Collectable::set_collect_sfx(const Ref<AudioStream> &sfx)
{
    p_collect_sound_effect = sfx;
}

Ref<AudioStream> Collectable::get_collect_sfx() const
{
    return p_collect_sound_effect;
}

void Collectable::_bind_methods()
{
    StringName &class_name = Collectable::get_class_static();

    ClassDB::bind_method(D_METHOD("set_game_state", "p_game_state"), &Collectable::set_game_state);
    ClassDB::bind_method(D_METHOD("get_game_state"), &Collectable::get_game_state);

    ClassDB::bind_method(D_METHOD("set_score_value", "p_score_value"), &Collectable::set_score_value);
    ClassDB::bind_method(D_METHOD("get_score_value"), &Collectable::get_score_value);

    ClassDB::bind_method(D_METHOD("set_collect_sfx", "p_sfx"), &Collectable::set_collect_sfx);
    ClassDB::bind_method(D_METHOD("get_collect_sfx"), &Collectable::get_collect_sfx);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "game_state", PROPERTY_HINT_RESOURCE_TYPE, GameState::get_class_static()), "set_game_state", "get_game_state");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "sfx", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_collect_sfx", "get_collect_sfx");
    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::INT, "score_value"), "set_score_value", "get_score_value");

    ClassDB::add_signal(class_name, MethodInfo(SIGNAL_ON_COLLECTED));
}
