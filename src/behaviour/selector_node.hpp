#ifndef _SELECTOR_NODE_H_
#define _SELECTOR_NODE_H_

#include "composite_node.hpp"

using namespace godot;

namespace behaviour
{
    class SelectorNode : public CompositeNode
    {
    public:
        BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) override;
    };
};

#endif