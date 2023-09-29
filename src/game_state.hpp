#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "audio_controller.hpp"

namespace godot
{
    class GameState : public Resource
    {
        GDCLASS(GameState, Resource)

    public:
        GameState();
        ~GameState();

        void add_score(const int amount);

        void audio_play(const Ref<AudioStream> &stream, const Vector2 &position, const float &volume, const float &max_distance, const StringName &bus);
        void audio_stop_all();

        void set_score(const uint32_t amount);
        uint32_t get_score() const;

    protected:
        static void _bind_methods();

    private:
        friend class AudioController;
        AudioController *p_audio_controller;

        uint32_t m_score;
    };
}

#endif
