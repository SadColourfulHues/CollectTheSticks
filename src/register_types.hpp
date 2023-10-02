#ifndef _REGISTER_TYPES_H_
#define _REGISTER_TYPES_H_

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

#include "core/game_state.hpp"
#include "core/audio_controller.hpp"

#include "player/player_controller.hpp"
#include "player/player_camera.hpp"

#include "collectable/collectable.hpp"
#include "collectable/stick.hpp"

#include "stick_eater/stick_eater.hpp"
#include "tree/tree_controller.hpp"

void initialise_module();
void terminate_module();

#endif
