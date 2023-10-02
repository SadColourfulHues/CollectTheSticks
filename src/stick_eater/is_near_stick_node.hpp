#ifndef _IS_NEAR_STICK_NODE_H_
#define _IS_NEAR_STICK_NODE_H_

#include "behaviour/behaviour_node.hpp"
#include "core/maths_utils.hpp"

#define NEAR_STICK_DISTANCE_THRESHOLD 1024

using namespace godot;
using namespace behaviour;

namespace game
{
    class IsNearStickNode : public BehaviourNode
    {
    public:
        BehaviourNodeResult process(double tick, Ref<BehaviourContext> context) override;
    };
};

#endif