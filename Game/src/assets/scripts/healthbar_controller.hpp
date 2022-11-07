#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "types.hpp"

class healtbar_controller : public brown::scriptable_entity
{
public:
    void health_changed(brown::event& e)
    {
        m_health = e.get_param<int>(Events::Player::Health::HEALTH);
    }

    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::HEALTH, healtbar_controller::health_changed));
        m_healthbar = &get_component<ui>();
        //pl = static_cast<player_controller*>(m_state->find_entity("player").get_component<native_script>().instance);
    }
    void on_update()
    {
        //m_health = pl->health;
        std::string hearts;
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = "Health: " + hearts;
    }

    void set_health(int health)
    {
        m_health = health;
    }

private:
    //player_controller *pl = nullptr;
    ui *m_healthbar = nullptr;
    int m_health = 10;
};
