#pragma once
#include "assets/inventory/item.hpp"
#include "assets/scripts/player_controller.hpp"

class boss_key : public artifact
{
public:
    boss_key() {
        this->m_name = "Boss room key";
    }

    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()), boss_key::on_interact));
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
    };

    void on_destroy()
    {
        m_state->remove_event_listener(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()));
    };

    void on_pickup(player_controller* pl) {
        m_state->send_event(Events::Room::Key_picked_up);
    }

    void on_remove() {}

    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(2))
        {
            m_player->add_item(new boss_key(*this));
            delete_self();
        }
    }
};