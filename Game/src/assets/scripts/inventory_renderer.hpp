#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "assets/inventory/inventory.hpp"
#include <vector>

class inventory_renderer : public brown::scriptable_entity
{
public:
    void on_inventory_changed(brown::event &e);
    void on_create();
    void on_update();
    void on_destroy();

private:
    int start_y = 7;

    std::vector<entity_id> m_entries;

    player_controller *m_player = nullptr;
};