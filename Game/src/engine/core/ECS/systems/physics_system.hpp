#pragma once
#include "../system.hpp"
#include "../../brain.hpp"
#include "../components/rigid_body.hpp"
#include "../components/force.hpp"

namespace brown
{
    class physics_system : public system
    {
    public:
        void init();
        void handle_events(brown::brain *br);
        void update(brain *br);
    };
}