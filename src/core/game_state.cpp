#include "game_state.hpp"

using namespace godot;


GameState::GameState()
{
    p_audio_controller = nullptr;
    m_score = 0;
}

GameState::~GameState()
{
}

void GameState::add_score(const int amount)
{
    set_score(m_score + abs(amount));
}

void GameState::set_score(const uint32_t score)
{
    m_score = score;
    emit_signal("score_changed", m_score);
}

uint32_t GameState::get_score() const
{
    return m_score;
}

void GameState::audio_play(const Ref<AudioStream> &stream, const Vector2 &position, const float &volume, const float &max_distance, const StringName &bus)
{
    if (p_audio_controller == nullptr)
        return;

    p_audio_controller->play(stream, position, volume, max_distance, bus);
}

void GameState::audio_stop_all()
{
    if (p_audio_controller == nullptr)
        return;

    p_audio_controller->stop_all();
}

void GameState::_bind_methods()
{
    StringName &class_name = GameState::get_class_static();

    ClassDB::bind_method(D_METHOD("get_score"), &GameState::get_score);
    ClassDB::bind_method(D_METHOD("set_score", "p_score"), &GameState::set_score);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::INT, "score"), "set_score", "get_score");

    // Signal: score_changed(score: int)
    ClassDB::add_signal(class_name, MethodInfo("score_changed", PropertyInfo(Variant::Type::INT, "score")));
}
