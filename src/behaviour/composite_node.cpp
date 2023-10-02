#include "composite_node.hpp"

using namespace behaviour;

CompositeNode::CompositeNode()
{
    memset(p_children, 0, MAX_COMPOSITE_NODE_CHILDREN * sizeof(Ref<BehaviourNode>));
}

CompositeNode::~CompositeNode()
{
    for (uint8_t i = 0; i < MAX_COMPOSITE_NODE_CHILDREN; ++i)
    {
        if (p_children[i].is_null())
            continue;

        p_children[i].unref();
    }
}

void CompositeNode::append(const Ref<BehaviourNode> &node)
{
    for (uint8_t i = 0; i < MAX_COMPOSITE_NODE_CHILDREN; ++i)
    {
        if (p_children[i].is_valid())
            continue;

        p_children[i] = node;
        break;
    }
}