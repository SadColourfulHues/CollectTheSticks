#ifndef _INVERT_NODE_H_
#define _INVERT_NODE_H_

#include "decorator_node.hpp"

using namespace godot;

namespace behaviour
{
    class InvertNode : public DecoratorNode
    {
    public:
        BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) override;
    };
};

#endif