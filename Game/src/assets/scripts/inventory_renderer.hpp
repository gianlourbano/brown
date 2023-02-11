#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "assets/inventory/inventory.hpp"
#include <vector>

class inventory_renderer : public brown::scriptable_entity
{
public:
    void on_inventory_changed(brown::event &e)
    {
        int i = 0;
        inventory *inv = m_player->get_inventory();
        auto items = inv->get_items();
        for (auto &item : items)
        {
            m_state->find_entity("entry_" + std::to_string(i)).get_component<ui>().text = "[" + item.i->name + "] x" + std::to_string(item.count);
            i++;
        }
    }

    void on_create()
    {
        inventory_renderer::add_component<transform>({0, 0});
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::Inventory::ADD,"inventory", inventory_renderer::on_inventory_changed));

        for (int i = 0; i < 10; i++)
        {
            auto entry = m_state->create_entity("entry_" + std::to_string(i));
            entry.add_component<transform>({vec2(1, start_y++)});
            entry.add_component<ui>({});
            m_entries.push_back(entry.get_id());
        }
    }

    void on_update()
    {
    }

    void on_destroy()
    {
    }

private:
    int start_y = 7;

    std::vector<entity_id> m_entries;

    player_controller *m_player = nullptr;
};