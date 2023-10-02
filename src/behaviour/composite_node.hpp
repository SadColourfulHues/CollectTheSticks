#ifndef _COMPOSITE_NODE_H_
#define _COMPOSITE_NODE_H_

#include <stdlib.h>
#include <cstdarg>
#include "behaviour_node.hpp"

#define MAX_COMPOSITE_NODE_CHILDREN 16

using namespace godot;

namespace behaviour
{
    class CompositeNode : public BehaviourNode
    {
    public:
        CompositeNode();
        virtual ~CompositeNode();

        void append(const Ref<BehaviourNode> &child);

    protected:
        Ref<BehaviourNode> p_children[MAX_COMPOSITE_NODE_CHILDREN];
    };
};

#endif