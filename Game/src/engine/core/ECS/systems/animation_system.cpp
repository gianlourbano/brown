#include "animation_system.hpp"
#include "../components/animation.hpp"

namespace brown
{
    void animation_system::init()
    {
    }

    void animation_system::update(brain *br, int dt)
    {
        for (auto &entity : m_entities)
        {
            auto &anim = br->get_component<animation>(entity);

            if (anim.playing && dt % anim.time_step == 0)
            {
                anim.current++;
            }
            if (anim.current == anim.clips)
            {
                if (anim.cyclic)
                {
                    anim.current = 0;
                }
                else if (anim.final)
                {
                    anim.playing = false;
                    anim.current--;
                }
                else
                {
                    anim.playing = false;
                    anim.current = 0;
                }
            }
        }
    }

    void animation_system::play(entity_id e, brain *brain)
    {
        auto &anim = brain->get_component<animation>(e);
        anim.current = 0;
        anim.playing = true;
    }

    void animation_system::stop(entity_id e, brain *brain)
    {
        auto &anim = brain->get_component<animation>(e);
        anim.playing = false;
        anim.current = 0;
    }
}
