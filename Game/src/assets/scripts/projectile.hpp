#pragma once
#include "brown.hpp"

class projectile : public brown::scriptable_entity
{
public:
    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
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
        } else {
            has_finished = true;
        }


        if(has_finished)
        {
            anim->play("explode", [this](){this->delete_self();});
            has_finished = false;
        }
    }

private:
    int lifetime;
    bool has_finished = false;
    vec2 force;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
};