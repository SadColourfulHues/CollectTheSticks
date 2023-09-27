#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    class GameState : public Resource
    {
        GDCLASS(GameState, Resource)

        private:
            uint32_t m_score;

        protected:
            static void _bind_methods();

        public:
            GameState();
            ~GameState();

            void add_score(const int amount);

            void set_score(const uint32_t amount);
            uint32_t get_score() const;
    };
}

#endif