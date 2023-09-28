#include "register_types.hpp"

using namespace godot;


void initialise_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    ClassDB::register_class<PlayerController>();
    ClassDB::register_class<PlayerCamera>();
    ClassDB::register_class<Collectable>();
    ClassDB::register_class<GameState>();
    ClassDB::register_class<TreeController>();
}

void terminate_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C"
{
    using namespace godot;

    GDExtensionBool GDE_EXPORT init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialisation)
    {
        GDExtensionBinding::InitObject init(p_get_proc_address, p_library, r_initialisation);

        init.register_initializer(initialise_module);
        init.register_terminator(terminate_module);

        init.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init.init();
    }
}
