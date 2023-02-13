#pragma once
#include "level_generator.hpp"
#include "math/mat.hpp"
#include "assets/scripts/player_controller.hpp"

class room_state;

class world_generator
{
public:
    using floorplan = brown::dt::vector<int>;
    using floorplans = brown::dt::vector<floorplan>;
    using generators = brown::dt::vector<level_generator>;
    using rooms = mat<room_state*>;
    using worlds = brown::dt::vector<rooms>;

    void generate_new_world(player_data data);
    void generate_neighbouring_rooms(int index);

    int get_current_world_index() { return m_current_world; }

    floorplan get_current_floorplan() {return m_floorplans[m_current_world];}
    rooms get_current_world() {return m_worlds[m_current_world];}

    room_state* get_room_for_current_world(int index) {return m_worlds[m_current_world][index];}

    bool is_fully_explored();

private:
    generators m_generators;
    floorplans m_floorplans;
    worlds m_worlds;

    const int m_world_size = 10;
    const int m_room_center = 45;

    int m_current_world = -1;
};