#ifndef _STICK_H_
#define _STICK_H_

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "collectable.hpp"

namespace godot
{
    class Stick : public Collectable
    {
        GDCLASS(Stick, Collectable)

    public:
        Stick();
        ~Stick();

        void _ready() override;
    };
};

#endif