#ifndef _WANDER_NODE_H_
#define _WANDER_NODE_H_

#include <godot_cpp/classes/random_number_generator.hpp>
#include "behaviour/behaviour_node.hpp"

#define WANDER_AVOID_OBSTACLE_DISTANCE 350.0

#define KEY_WANDER_DIR "wdir"
#define KEY_WANDER_TARGET_DIR "tdir"
#define KEY_WANDER_LAST_POSITION "wlp"

using namespace behaviour;
using namespace godot;

namespace game
{
    class WanderNode : public BehaviourNode
    {
    public:
        WanderNode();
        ~WanderNode();

        BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) override;

    private:
        float m_update_wander_tick;
        RandomNumberGenerator p_random;
    };
};

#endif