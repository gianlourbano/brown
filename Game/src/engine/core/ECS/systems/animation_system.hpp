#pragma once

#include "../system.hpp"
#include "../../brain.hpp"

namespace brown
{
    class animation_system : public system
    {
    public:
        void init();

        void update(brain* br, int dt);

        void play(entity_id e, brain *brain);

        void stop(entity_id e, brain *brain);
    };
}