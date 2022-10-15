#pragma once
#include "engine/brown.hpp"

// This is a simple script that will open and close a door when the player
class door_controller : public brown::scriptable_entity
{
    // This function is called when the script is created
    void on_create()
    {
        anim = &get_component<animator_controller>();
        ts = &get_component<transform>();
    }

    // This function is called every frame
    void on_update()
    {
        pt = this->m_state->find_entity("player").get_component<transform>().position;
        float range = distance(pt, ts->position);
        
        if (range <= 5.0  && !is_open)
        {
            anim->play("open");
        }
        if (range > 5.0 && is_open)
        {
            anim->play_reversed("open");
            LOG("DISTANT");
        }

        if(anim->current_anim->has_finished) {is_open != is_open;}
    }

private:
    animator_controller *anim = nullptr;
    transform *ts;
    vec2 pt;

    bool is_open = false;
};