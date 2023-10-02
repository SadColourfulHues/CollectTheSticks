#ifndef _BEHAVIOUR_CONTEXT_H_
#define _BEHAVIOUR_CONTEXT_H_

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/hash_map.hpp>

using namespace godot;

namespace behaviour
{
    class BehaviourContext final : public RefCounted
    {
    public:
        BehaviourContext();
        ~BehaviourContext();

        void clear();
        bool has_key(const StringName &key);

        void write(const StringName &key, const int &value);
        void write(const StringName &key, const double &value);
        void write(const StringName &key, const float &value);
        void write(const StringName &key, const bool &value);
        void write(const StringName &key, const Vector2 &value);

        void erase(const StringName &key);

        Variant read(const StringName &key, const Variant &default_value);
        int read_int(const StringName &key, const int &default_value = 0);
        double read_double(const StringName &key, const double &default_value = 0);
        float read_float(const StringName &key, const float &default_value = 0);
        bool read_bool(const StringName &key, const bool &default_value = false);
        Vector2 read_vector(const StringName &key, const Vector2 &default_value = Vector2(0, 0));

    private:
        HashMap<StringName, Variant> p_data;
    };
};

#endif