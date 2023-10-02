#ifndef _MOVE_TOWARDS_NODE_H_
#define _MOVE_TOWARDS_NODE_H_

#include "behaviour/behaviour_node.hpp"
#include "core/maths_utils.hpp"

#define MOVE_AVOID_OBSTACLE_DISTANCE 90.0

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