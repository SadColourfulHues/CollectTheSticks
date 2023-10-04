#ifndef _MOVE_TOWARDS_NODE_H_
#define _MOVE_TOWARDS_NODE_H_

#include "behaviour/behaviour_node.hpp"
#include "core/maths_utils.hpp"

using namespace godot;
using namespace behaviour;

namespace game
{
    class MoveTowardsNode : public BehaviourNode
    {
    public:
        BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) override;
    };
};

#endif