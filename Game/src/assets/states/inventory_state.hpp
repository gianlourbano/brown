#pragma once

#include "engine/brown.hpp"
#include "assets/inventory/inventory.hpp"

class inventory_state : public brown::state
{
public:
    inventory_state(inventory* inv): m_inventory(inv->get_items_vector()), m_inventory_ptr(inv) {}

    void init(brown::engine* game);
    
    void cleanup();
    void pause();
    void resume();

    void handle_events(brown::engine* game);
    void update(brown::engine* game);
    void draw(brown::engine* game);

private:
    brown::dt::vector<item*> m_inventory;
    inventory* m_inventory_ptr;
    item* m_current_item;
    int m_current_item_index = 0;
    brown::entity arrow;

    std::shared_ptr<brown::UI_system> m_UI_system;
    std::shared_ptr<brown::animation_system> m_animation_system;
};