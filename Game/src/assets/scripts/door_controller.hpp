#pragma once
#include "engine/brown.hpp"

#include "assets/states/room_state.hpp"

struct door_data
{
    room_state *room = nullptr;
    room_state *last_room = nullptr;
    int id = -1;
    bool vertical = false;

    bool entrance = false;
    int dir = 0;

    door_data() {}
    door_data(room_state *room, room_state *last_room, int id, bool vertical, bool entrance, int dir = 0)
    {
        this->room = room;
        this->last_room = last_room;
        this->id = id;
        this->vertical = vertical;
        this->entrance = entrance;
        this->dir = dir;
    }
};

// This is a simple script that will open and close a door when the player
class door_controller : public brown::scriptable_entity
{
public:
    door_controller(door_data data) : data(data) {}

    // This function is called when the script is created
    void on_create()
    {
        anim = &get_component<animator_controller>();
        ts = &get_component<transform>();
    }

    // This function is called every frame
    void on_update()
    {
        pt = this->m_state->find_entity("player").get_component<transform>().position;
        float range = distance(pt, ts->position);

        if (range <= 5.0 && !is_open)
        {
            anim->play("open");
        }

        if (!data.vertical && pt.x >= ts->position.x && pt.x <= ts->position.x + 4 && pt.y >= ts->position.y && pt.y <= ts->position.y + 1)
        {
            player_controller *pc = dynamic_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);

            if (data.entrance)
            {
                room_data *rd = data.room->get_data();

                rd->m_player_data = pc->get_data();

                m_state->get_game_instance()->pop_state();
            }
            else
            {
                room_data *rd = data.room->get_data();
                rd->m_player_data = pc->get_data();
                m_state->get_game_instance()->push_state(data.room);
            }

            transform *tsp = &m_state->find_entity("player").get_component<transform>();
            if (data.dir == 1)
                tsp->position.y -= 2;
            if (data.dir == 3)
                tsp->position.y += 2;
        }

        else if (data.vertical && pt.x >= ts->position.x && pt.x <= ts->position.x + 1 && pt.y >= ts->position.y && pt.y <= ts->position.y + 2)
        {
            player_controller *pc = dynamic_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);

            if (data.entrance)
            {
                room_data *rd = data.room->get_data();
                rd->m_player_data = pc->get_data();
                m_state->get_game_instance()->pop_state();
            }
            else
            {
                room_data *rd = data.room->get_data();
                rd->m_player_data = pc->get_data();
                m_state->get_game_instance()->push_state(data.room);
            }

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
    bool is_open = false;

private:
    animator_controller *anim = nullptr;
    transform *ts;
    vec2 pt;

    door_data data;
};