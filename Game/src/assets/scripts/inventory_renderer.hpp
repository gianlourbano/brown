#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "assets/inventory/inventory.hpp"
#include <vector>



class inventory_renderer : public brown::scriptable_entity
{
public:
    void on_item_added(brown::event& e) {
        inventory_item i = e.get_param<inventory_item>(Events::Player::Inventory::ADD);

        auto entry = m_state->create_entity();
        entry.add_component<transform>({vec2(1, start_y++)});
        entry.add_component<ui>({"[" + i.i->name + "] x" + std::to_string(i.count) });
    
    }

    void on_create()
    {
        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::Inventory::ADD,"inventory", inventory_renderer::on_item_added));

        inventory* items = m_player->get_inventory();
    }

    void on_update()
    {
        
    }

    void on_destroy()
    {
    }

private:
    int start_y = 9;

    std::vector<entity_id> m_entries;

    player_controller *m_player = nullptr;
};