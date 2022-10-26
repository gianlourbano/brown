#pragma once
#include "engine/brown.hpp"

class healtbar_controller : public brown::scriptable_entity
{
public:

    void on_create()
    {
        m_healthbar = &get_component<ui>();
    }
    void on_update()
    {
        std::string hearts;
        for(int i = 0; i < m_health; i++)
        {
            hearts += "❤ ";
        }
        m_healthbar->text = "Health: " + hearts;
    }

    void set_health(int health)
    {
        m_health = health;
    }

private:
    brown::scriptable_entity* pl;
    ui *m_healthbar = nullptr;
    int m_health = 10;
};
