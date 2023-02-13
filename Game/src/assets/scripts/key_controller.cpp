#include "assets/scripts/key_controller.hpp"

    virtual void key_controller::on_iteract(){
        room_data *rd = data.room->get_data();
        rd->key = true;
    }
