#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "game_state.hpp"

#define TAG_COLLECTABLE "collectables"

namespace godot
{
    class Collectable : public StaticBody2D
    {
        GDCLASS(Collectable, StaticBody2D)

        private:
            Ref<GameState> p_game_state;
            uint32_t m_score_value;

        protected:
            static void _bind_methods();

        public:
            Collectable();
            ~Collectable();

            void collect();

            void set_game_state(const Ref<GameState> &state);
            Ref<GameState> get_game_state() const;

            void set_score_value(const uint32_t value);
            uint32_t get_score_value() const;
    };
}

#endif