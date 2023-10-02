#include "decorator_node.hpp"

using namespace behaviour;

DecoratorNode::DecoratorNode()
{
}

DecoratorNode::~DecoratorNode()
{
    if (p_target.is_null())
        return;

    p_target.unref();
}

void DecoratorNode::set_target(const Ref<BehaviourNode> &target)
{
    p_target = target;
}