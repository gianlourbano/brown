#pragma once
#include "assets/inventory/item.hpp"
#include "assets/scripts/player_controller.hpp"

struct potion : public consumable
{
public:
    potion(int intensity) : m_health(intensity)
    {
        this->name = "Potion";
    };

    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID,"Potion_"+std::to_string(m_entity.get_id()), potion::on_interact));
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
    };
    void on_update(){};
    void on_destroy(){
        m_state->remove_event_listener(Events::Entity::Interact::ID, "Potion_"+std::to_string(m_entity.get_id()));
    };

    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(2))
        {
            m_player->add_item(this);
            delete_self();
        }
    };

    void on_use()
    {
        m_player->set_health(m_player->get_health() + m_health);
    };

private:
    player_controller *m_player;
    int m_health;
};