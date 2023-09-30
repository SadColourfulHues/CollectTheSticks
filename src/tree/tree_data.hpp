#ifndef _TREE_DATA_H_
#define _TREE_DATA_H_

#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot
{
    typedef struct tree_data_t
    {
        RID visual_rid;
        RID body_rid;

        Vector2 position;

        tree_data_t(const RID &visual_rid, const Vector2 &position)
        {
            this->visual_rid = visual_rid;
            this->position = position;

            body_rid = RID();
        }
    }
    TreeData;
}

#endif
