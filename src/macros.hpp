#ifndef _MACROS_H_
#define _MACROS_H_

#include <godot_cpp/classes/engine.hpp>

#define NO_EDITOR if (Engine::get_singleton()->is_editor_hint()) return;

#endif