#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "game_state.hpp"

#define TAG_COLLECTABLE "collectables"
#define SIGNAL_ON_COLLECTED "on_collected"

namespace godot
{
    class Collectable : public StaticBody2D
    {
        GDCLASS(Collectable, StaticBody2D)

    public:
        Collectable();
        ~Collectable();

        virtual void _ready() {}

        void collect();

        void set_game_state(const Ref<GameState> &state);
        Ref<GameState> get_game_state() const;

        void set_score_value(const uint32_t value);
        uint32_t get_score_value() const;

        void set_collect_sfx(const Ref<AudioStream> &sfx);
        Ref<AudioStream> get_collect_sfx() const;

    protected:
        static void _bind_methods();

        Ref<AudioStream> p_collect_sound_effect;

    private:
        Ref<GameState> p_game_state;
        uint32_t m_score_value;
    };
}

#endif
