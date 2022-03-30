#pragma once
#include "brown.hpp"

class projectile : public brown::scriptable_entity
{
public:
    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animation>();
        lifetime = 10;

        switch (ts->direction)
        {
        case 1:
            force = {0, -1};
            lifetime /= 2;
            break;
        case 2:
            force = {1, 0};
            break;
        case 3:
            force = {0, 1};
            lifetime /= 2;
            break;
        case 4:
            force = {-1, 0};
            break;
        }
    }

    void on_update()
    {
        if (lifetime != 0)
        {
            ts->position += force;
            lifetime--;
        }
        else
        {
            if (!anim->playing)
                anim->playing = true;
            if (anim->current == anim->clips -1)
            {
                delete_self();
            }
        }
    }

private:
    int lifetime;
    vec2 force;
    transform *ts = nullptr;
    animation *anim = nullptr;
};