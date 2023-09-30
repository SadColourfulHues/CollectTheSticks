#ifndef _SELECTOR_NODE_H_
#define _SELECTOR_NODE_H_

#include "composite_node.hpp"

namespace godot
{
    class SelectorNode : public CompositeNode
    {
    public:
        BehaviourNodeResult process(double delta) override;
    };
};

#endif