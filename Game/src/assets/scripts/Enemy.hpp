#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"

class scriptable_enemy : public scriptable_AI
{
public:
    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(6))
        {
           m_health--;
        }
    }

    void on_create()
    {
        ts = &get_component<transform>();
        m_healthbar = &get_component<ui>();

        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, scriptable_enemy::on_interact));

        m_health = 3;
    };
    void on_update()
    {
        std::string hearts = "";
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;

        if(m_health <= 0) {
            delete_self();
        }
    }
    void on_destroy()
    {
        //m_state->remove_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, scriptable_enemy::on_interact));
    }
    
private:
    int m_health;
    ui *m_healthbar;
};
