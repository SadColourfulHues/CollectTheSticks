#include "behaviour_context.hpp"

using namespace behaviour;

BehaviourContext::BehaviourContext()
{
}

BehaviourContext::~BehaviourContext()
{
    clear();
}

void BehaviourContext::clear()
{
    p_data.clear();
}

bool BehaviourContext::has_key(const StringName &key)
{
    return p_data.has(key);
}

void BehaviourContext::write(const StringName &key, const int &value)
{
    p_data[key] = value;
}

void BehaviourContext::write(const StringName &key, const double &value)
{
    p_data[key] = value;
}

void BehaviourContext::write(const StringName &key, const float &value)
{
    p_data[key] = value;
}

void BehaviourContext::write(const StringName &key, const bool &value)
{
    p_data[key] = value;
}

void BehaviourContext::write(const StringName &key, const Vector2 &value)
{
    p_data[key] = value;
}

void BehaviourContext::erase(const StringName &key)
{
    p_data.erase(key);
}

Variant BehaviourContext::read(const StringName &key, const Variant &default_value)
{
    if (!p_data.has(key))
        return default_value;

    return p_data[key];
}

int BehaviourContext::read_int(const StringName &key, const int &default_value)
{
    return static_cast<int>(read(key, default_value));
}

double BehaviourContext::read_double(const StringName &key, const double &default_value)
{
    return static_cast<double>(read(key, default_value));
}

float BehaviourContext::read_float(const StringName &key, const float &default_value)
{
    return static_cast<float>(read(key, default_value));
}

bool BehaviourContext::read_bool(const StringName &key, const bool &default_value)
{
    return static_cast<bool>(read(key, default_value));
}

Vector2 BehaviourContext::read_vector(const StringName &key, const Vector2 &default_value)
{
    return static_cast<Vector2>(read(key, default_value));
}