#pragma once
#include "brown.hpp"
#include "assets/inventory/inventory.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
#include "assets/states/room_state.hpp"
struct key_data{

    room_state *room;
    bool key;
};

class key : public consumable
{
    public:
    virtual void on_iteract(){
    }
    
    private:
        key_data data;
};
