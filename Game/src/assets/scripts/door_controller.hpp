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
    void on_create();

    // This function is called every frame
    void on_update();
    bool is_open = false;

protected:
    animator_controller *anim = nullptr;
    transform *ts;
    vec2 pt;

    door_data data;
};