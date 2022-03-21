#pragma once

#include "../system.hpp"
#include "../../brain.hpp"

namespace brown
{
    class animation_system : public system
    {
    public:
        static std::shared_ptr<animation_system> register_system(brown::brain* br);

        void init();

        void update(brain* br, int dt);

        static void play(entity_id e, brain *brain);

        static void stop(entity_id e, brain *brain);
    };
}