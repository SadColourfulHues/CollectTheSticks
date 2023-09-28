#ifndef _REGISTER_TYPES_H_
#define _REGISTER_TYPES_H_

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

#include "player_controller.hpp"
#include "player_camera.hpp"
#include "game_state.hpp"
#include "collectable.hpp"
#include "tree_controller.hpp"

void initialise_module();
void terminate_module();

#endif
