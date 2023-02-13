#pragma once
#include "assets/inventory/item.hpp"
#include "assets/scripts/player_controller.hpp"

class offensive_charm : public artifact
{
public:
    offensive_charm(int atk): m_attack(atk) {
        this->m_name = "Offensive Charm (+ " + std::to_string(atk) +")";
    }

    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()), offensive_charm::on_interact));
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
    };

    void on_destroy()
    {
        m_state->remove_event_listener(Events::Entity::Interact::ID, m_name + std::to_string(m_entity.get_id()));
    };


    void on_pickup(player_controller* pc) {
        m_player->set_attack(pc->get_attack() + m_attack);

    }

    void on_remove() {
        m_player->set_attack(m_player->get_attack() - m_attack);
    }

    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(2))
        {
            m_player->add_item(new offensive_charm(*this));
            delete_self();
        }
    }

private:
    int m_attack = 0;
};