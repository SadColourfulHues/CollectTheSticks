#ifndef _DECORATOR_NODE_H_
#define _DECORATOR_NODE_H_

#include "behaviour_node.hpp"

using namespace godot;

namespace behaviour
{
    class DecoratorNode : public BehaviourNode
    {
    public:
        DecoratorNode();
        virtual ~DecoratorNode();

        void set_target(const Ref<BehaviourNode> &target);

    protected:
        Ref<BehaviourNode> p_target;
    };
};

#endif