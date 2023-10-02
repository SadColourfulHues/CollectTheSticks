#ifndef _SEQUENCE_NODE_H_
#define _SEQUENCE_NODE_H_

#include "composite_node.hpp"

using namespace godot;

namespace behaviour
{
    class SequenceNode : public CompositeNode
    {
    public:
        BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) override;
    };
};

#endif