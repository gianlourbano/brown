#pragma once
#include "door_controller.hpp"

class boss_door_controller : public door_controller
{
public:
    boss_door_controller(door_data data) : door_controller(data){};

    void on_create() {
        door_controller::on_create();

       }

    void on_update()
    {
        pt = this->m_state->find_entity("player").get_component<transform>().position;
        float range = distance(pt, ts->position);

        if (range <= 5.0 && !is_open && data.room->get_data()->world_gen->get_current_generator()->is_unlocked())
        {
            anim->play("open");
            is_open = true;
        }

        if (!data.vertical && pt.x >= ts->position.x && pt.x <= ts->position.x + 4 && pt.y >= ts->position.y && pt.y <= ts->position.y + 1)
        {
            player_controller *pc = dynamic_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);

            room_data *rd = data.room->get_data();
            rd->m_player_data = pc->get_data();


                m_state->get_game_instance()->push_state(data.room);

            transform *tsp = &m_state->find_entity("player").get_component<transform>();
            if (data.dir == 1)
                tsp->position.y -= 2;
            if (data.dir == 3)
                tsp->position.y += 2;
        }

        else if (data.vertical && pt.x >= ts->position.x && pt.x <= ts->position.x + 1 && pt.y >= ts->position.y && pt.y <= ts->position.y + 2)
        {
            player_controller *pc = dynamic_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);

            room_data *rd = data.room->get_data();
            rd->m_player_data = pc->get_data();

                m_state->get_game_instance()->push_state(data.room);

            transform *tsp = &m_state->find_entity("player").get_component<transform>();
            if (data.dir == 4)
                tsp->position.x -= 2;
            if (data.dir == 2)
                tsp->position.x += 2;
        }

        if (anim->current_anim->has_finished)
        {
            is_open = !is_open;
        }
    }
};