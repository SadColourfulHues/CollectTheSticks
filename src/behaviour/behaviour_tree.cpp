#include "behaviour_tree.hpp"

using namespace behaviour;

BehaviourTree::BehaviourTree()
{
    p_context.instantiate();
}

BehaviourTree::~BehaviourTree()
{
    p_context.unref();

    if (p_root.is_null())
        return;

    p_root.unref();
}

void BehaviourTree::set_root(const Ref<BehaviourNode> &root)
{
    if (root.is_null())
    {
        ERR_PRINT("BehaviourTree: <root> is set to null!");
        return;
    }

    p_root = root;
}

Ref<BehaviourContext> BehaviourTree::get_context() const
{
    return p_context;
}

void BehaviourTree::process(double delta)
{
    p_root->process(delta, p_context);
}