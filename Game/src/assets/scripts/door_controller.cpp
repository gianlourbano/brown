#include "assets/scripts/door_controller.hpp"

void door_controller::on_create()
{
    anim = &get_component<animator_controller>();
    ts = &get_component<transform>();
    }

    void door_controller::on_update()
    {
        pt = this->m_state->find_entity("player").get_component<transform>().position;
        float range = distance(pt, ts->position);
        
        if (range <= 5.0 && !is_open && data.last_room == nullptr)
        {
            anim->play("open");
        }

        else if (range <= 5.0 && !is_open && data.last_room->is_room_cleared())
        {
            anim->play("open");
        }

        if (!data.vertical && pt.x >= ts->position.x && pt.x <= ts->position.x + 4 && pt.y >= ts->position.y && pt.y <= ts->position.y + 1)
        {
            player_controller *pc = dynamic_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);

            room_data *rd = data.room->get_data();
            rd->m_player_data = pc->get_data();

            if (data.entrance)
                m_state->get_game_instance()->pop_state();
            else
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

            if (data.entrance)
                m_state->get_game_instance()->pop_state();
            else
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
