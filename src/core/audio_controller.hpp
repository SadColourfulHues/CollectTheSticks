#ifndef _AUDIO_CONTROLLER_H_
#define _AUDIO_CONTROLLER_H_

#include <stdlib.h>
#include <vector>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>

#define MAX_AUDIO_PLAYBACK 24
#define SFX_DEFAULT_DISTANCE 300

#define BUS_MASTER "Master"
#define BUS_SFX "SFX"
#define BUS_BGM "BGM"

using namespace godot;

namespace game
{
    class AudioController : public Node2D
    {
        GDCLASS(AudioController, Node2D)

    public:
        AudioController();
        ~AudioController();

        void _ready() override;

        void play(const Ref<AudioStream> &stream, const Vector2 &position, const float &volume = 1.0f, const float &max_distance = SFX_DEFAULT_DISTANCE, const StringName &bus = BUS_MASTER);
        void stop_all();

        void set_game_state(const Ref<Resource> &game_state);
        Ref<Resource> get_game_state() const;

    private:
        static void _bind_methods();
        void pool_get_player(AudioStreamPlayer2D **player_ref);

        Ref<Resource> p_game_state;
        AudioStreamPlayer2D *p_players[MAX_AUDIO_PLAYBACK];
    };
};

#endif