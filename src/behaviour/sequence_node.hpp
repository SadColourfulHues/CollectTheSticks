#ifndef _SEQUENCE_NODE_H_
#define _SEQUENCE_NODE_H_

#include "composite_node.hpp"

namespace godot
{
    class SequenceNode : public CompositeNode
    {
    public:
        BehaviourNodeResult process(double delta) override;
    };
};

#endif