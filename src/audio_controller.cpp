#include "audio_controller.hpp"
#include "game_state.hpp"

using namespace godot;

AudioController::AudioController()
{
    memset(p_players, 0, MAX_AUDIO_PLAYBACK * sizeof(Ref<AudioStreamPlayer2D>));
}

AudioController::~AudioController()
{
    for (int i = 0; i < MAX_AUDIO_PLAYBACK; ++i)
    {
        if (p_players[i] == NULL)
            continue;

        p_players[i]->queue_free();
    }

    if (p_game_state.is_null())
        return;

    GameState *game_state = static_cast<GameState *>(p_game_state.ptr());

    if (game_state->p_audio_controller != this)
        return;

    game_state->p_audio_controller = nullptr;
}

void AudioController::_ready()
{
    if (Engine::get_singleton()->is_editor_hint() || p_game_state.is_null())
        return;

    GameState *game_state = static_cast<GameState *>(p_game_state.ptr());
    game_state->p_audio_controller = this;
}

void AudioController::play(const Ref<AudioStream> &stream, const Vector2 &position, const float &volume, const float &max_distance, const StringName &bus)
{
    AudioStreamPlayer2D *player = nullptr;
    pool_get_player(&player);

    if (player == nullptr)
        return;

    player->set_bus(bus);
    player->set_stream(stream);
    player->set_global_position(position);
    player->set_max_distance(max_distance);
    player->set_volume_db(Math::linear2db(volume));

    player->play();
}

void AudioController::stop_all()
{
    for (int i = 0; i < MAX_AUDIO_PLAYBACK; ++i)
    {
        if (p_players[i] == nullptr || !p_players[i]->is_playing())
            return;

        p_players[i]->stop();
    }
}

void AudioController::pool_get_player(AudioStreamPlayer2D **player_ref)
{
    int open_index = -1;

    for (int i = 0; i < MAX_AUDIO_PLAYBACK; ++i)
    {
        if (p_players[i] == NULL)
        {
            if (open_index == -1)
            {
                open_index = i;
            }

            continue;
        }

        if (p_players[i]->is_playing())
            continue;

        *player_ref = p_players[i];
        return;
    }

    if (open_index == -1)
    {
        *player_ref = nullptr;
        return;
    }

    AudioStreamPlayer2D *player = memnew(AudioStreamPlayer2D);
    *player_ref = player;

    p_players[open_index] = player;
    add_child(player);
}

void AudioController::set_game_state(const Ref<Resource> &game_state)
{
    p_game_state = game_state;
}

Ref<Resource> AudioController::get_game_state() const
{
    return p_game_state;
}

void AudioController::_bind_methods()
{
    StringName &class_name = AudioController::get_class_static();

    ClassDB::bind_method(D_METHOD("play", "stream", "position", "volume", "max_distance", "bus"), &AudioController::play);
    ClassDB::bind_method(D_METHOD("stop_all"), &AudioController::stop_all);

    ClassDB::bind_method(D_METHOD("set_game_state", "p_game_state"), &AudioController::set_game_state);
    ClassDB::bind_method(D_METHOD("get_game_state"), &AudioController::get_game_state);

    ClassDB::add_property(class_name, PropertyInfo(Variant::Type::OBJECT, "game_state", PROPERTY_HINT_RESOURCE_TYPE, GameState::get_class_static()), "set_game_state", "get_game_state");
}
