#ifndef _BEHAVIOUR_TREE_H_
#define _BEHAVIOUR_TREE_H_

#include <godot_cpp/classes/ref_counted.hpp>
#include "behaviour_node.hpp"

using namespace godot;

namespace behaviour
{
    class BehaviourTree : public RefCounted
    {
    public:
        BehaviourTree();
        ~BehaviourTree();

        void set_root(const Ref<BehaviourNode> &root);
        void process(double tick);

        Ref<BehaviourContext> get_context() const;

    private:
        Ref<BehaviourNode> p_root;
        Ref<BehaviourContext> p_context;
    };
};

#endif