#ifndef _TREE_DATA_H_
#define _TREE_DATA_H_

#include <godot_cpp/classes/rendering_server.hpp>

namespace godot
{
    typedef struct tree_data_t
    {
        RID visual_rid;
        RID body_rid;

        Vector2 position;

        tree_data_t()
        {
            visual_rid = RID();
            body_rid = RID();

            position = Vector2(0, 0);
        }
    }
    TreeData;
}

#endif
