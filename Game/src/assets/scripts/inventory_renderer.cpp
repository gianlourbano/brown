#include "assets/inventory/inventory_renderer.hpp"

    void inventory_renderer::on_inventory_changed(brown::event &e)
    {
        int i = 0;
        inventory *inv = m_player->get_inventory();
        if(inv == nullptr)
            return;
        auto items = inv->get_items();
        for (auto &item : items)
        {
            m_state->find_entity("entry_" + std::to_string(i)).get_component<ui>().text = "[" + item->m_name + "] x" + std::to_string(item->m_count);
            i++;
        }

        for(; i < 10; i++)
            m_state->find_entity("entry_" + std::to_string(i)).get_component<ui>().text = " ";
    }

    void inventory_renderer::on_create()
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

        m_state->send_event(Events::Player::Inventory::ADD);

    }

    void inventory_renderer::on_update()
    {
        // int i = 0;
        // inventory *inv = m_player->get_inventory();
        // auto items = inv->get_items();
        // for (auto &item : items)
        // {
        //     m_state->find_entity("entry_" + std::to_string(i)).get_component<ui>().text = "[" + item->m_name + "] x" + std::to_string(item->m_count);
        //     i++;
        // }

        // for(; i < 10; i++)
        //     m_state->find_entity("entry_" + std::to_string(i)).get_component<ui>().text = " ";
    }

    void inventory_renderer::on_destroy()
    {
    }