#include "maths_utils.hpp"

float game::distance_between(const Vector2 &a, const Vector2 &b)
{
    return Math::abs((Math::abs(a.x) - Math::abs(b.x)) + (Math::abs(a.y) - Math::abs(b.y)));
}