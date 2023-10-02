#ifndef _BEHAVIOUR_NODE_H_
#define _BEHAVIOUR_NODE_H_

#include <godot_cpp/classes/ref_counted.hpp>
#include "behaviour_context.hpp"

using namespace godot;

namespace behaviour
{
    enum BehaviourNodeResult
    {
        PROCESS_FAIL,
        PROCESS_SUCCESS,
        PROCESS_RUNNING
    };

    class BehaviourNode : public RefCounted
    {
    public:
        virtual ~BehaviourNode();
        virtual BehaviourNodeResult process(double delta, Ref<BehaviourContext> context) = 0;

    protected:
        BehaviourNode();
    };
};

#endif