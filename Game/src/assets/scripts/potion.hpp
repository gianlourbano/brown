#pragma once
#include "brown.hpp"
#include "assets/inventory/inventory.hpp"
#include "assets/scripts/player_controller.hpp"

class potion : public consumable
{
    virtual void on_use(){
        player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        pl_h->add1_health();
    }
};
