#pragma once
#include "engine/brown.hpp"

class logo_controller : public brown::scriptable_entity
{
public:
    void on_create() {
        ts = &get_component<transform>();
    }

    void on_update()
    {
        if (m_counter < 10)
        {
            if(m_timer.elapsed() >= 0.05)
            {
                m_counter++;
                m_timer.start();
                ts->position.y++;
            }
        }
    }

private:
    transform *ts;
    int m_counter = 0;

    brown::Timer m_timer;
};