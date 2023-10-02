#ifndef _MATHS_UTILS_H_
#define _MATHS_UTILS_H_

#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

namespace game
{
    float distance_between(const Vector2 &a, const Vector2 &b);
}

#endif