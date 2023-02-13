#pragma once
#include "assets/inventory/item.hpp"
#include "assets/scripts/player_controller.hpp"

class vitality_charm : public artifact
{
public:
    vitality_charm() {
        this->m_name = "Vitality Charm";
    }

    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()), vitality_charm::on_interact));
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
    };

    void on_destroy()
    {
        m_state->remove_event_listener(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()));
    };


    void on_pickup(player_controller* pc) {
        pc->set_max_health(pc->get_max_health() + 20);
    }

    void on_remove() {
        m_player->set_max_health(m_player->get_max_health() - 20);
    }

    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(2))
        {
            m_player->add_item(new vitality_charm(*this));
            delete_self();
        }
    }
};