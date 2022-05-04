#include "animation_system.hpp"
#include "../components/animation.hpp"
#include "core/ECS/components/animator_controller.hpp"
#include "core/ECS/components/sprite.hpp"
#include "core/ECS/components/transform.hpp"
#include <map>

namespace brown
{
    std::map<entity_id, sprite> animated;

    std::shared_ptr<animation_system> brown::animation_system::register_system(brown::brain *br)
    {
        std::shared_ptr<animation_system> sys = br->register_system<brown::animation_system>();
        signature signature;
        signature.set(br->get_component_type<transform>());
        signature.set(br->get_component_type<animator_controller>());
        signature.set(br->get_component_type<sprite>());
        br->set_system_signature<brown::animation_system>(signature);
        return sys;
    }

    void animation_system::init()
    {
    }

    void animation_system::update(brain *br, int dt)
    {
        for (auto &entity : m_entities)
        {
            auto &animator = br->get_component<animator_controller>(entity);
            auto &spr = br->get_component<sprite>(entity);
            auto &tr = br->get_component<transform>(entity);
            auto anim = animator.current_anim;

            if (anim != nullptr)
            {
                if (anim->playing && dt % anim->time_step == 0)
                {
                    animated.insert(std::make_pair(entity, spr));

                    spr.sprite_name = anim->name + std::to_string(anim->current);
                    spr.offset = anim->offset;
                    anim->current++;
                }
                if (anim->current == anim->clips)
                {
                    if (anim->cyclic)
                    {
                        anim->current = 0;
                    }
                    else if (anim->final)
                    {
                        anim->has_finished = true;
                        anim->playing = false;
                        animated.erase(entity);
                    }
                    else
                    {
                        anim->has_finished = true;
                        anim->playing = false;
                        anim->current = 0;
                        spr = animated[entity];
                        animated.erase(entity);
                    }
                }
            }
        }
    }

    void animation_system::play(entity_id e, brain *brain)
    {
        auto &anim = brain->get_component<animator_controller>(e);
        anim.current_anim->current = 0;
        anim.current_anim->playing = true;
    }

    void animation_system::stop(entity_id e, brain *brain)
    {
        auto &anim = brain->get_component<animation>(e);
        anim.playing = false;
        anim.current = 0;
    }
}
