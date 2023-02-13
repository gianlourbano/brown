#include "world_generator.hpp"
#include "assets/states/room_state.hpp"
#include "assets/states/boss_room_state.hpp"

void world_generator::generate_new_world(player_data data)
{
    m_generators.push_back(level_generator(m_current_world));
    m_generators.back().generate();

    m_floorplans.push_back(m_generators.back().get_floorplan());

    rooms new_world = rooms(10, 10);
    m_worlds.push_back(new_world);

    m_worlds.back()[this->m_room_center] = new room_state(room_data(45, data, this, 0));
    m_floorplans.back()[this->m_room_center] += 1;

    m_current_world++;
};

void world_generator::generate_neighbouring_rooms(int index)
{
    floorplan fp = m_floorplans[m_current_world];

    if (fp[index - 1] == 1 || fp[index - 1] == 5)
    {
        m_worlds[m_current_world][index - 1] = new room_state(room_data(index - 1, player_data(), this, 2));
        m_floorplans[m_current_world][index - 1] += 1;
    }
    else if (fp[index - 1] == 3)
    {
        m_worlds[m_current_world][index - 1] = new boss_room_state(room_data(index - 1, player_data(), this, 2));
        m_floorplans[m_current_world][index - 1] += 1;
    }
    if (fp[index + 1] == 1 || fp[index + 1] == 5)
    {
        m_worlds[m_current_world][index + 1] = new room_state(room_data(index + 1, player_data(), this, 4));
        m_floorplans[m_current_world][index + 1] += 1;
    }
    else if (fp[index + 1] == 3)
    {
        m_worlds[m_current_world][index + 1] = new boss_room_state(room_data(index + 1, player_data(), this, 4));
        m_floorplans[m_current_world][index + 1] += 1;
    }
    if (fp[index - 10] == 1 || fp[index - 10] == 5)
    {
        m_worlds[m_current_world][index - 10] = new room_state(room_data(index - 10, player_data(), this, 3));
        m_floorplans[m_current_world][index - 10] += 1;
    }
    else if (fp[index - 10] == 3)
    {
        m_worlds[m_current_world][index - 10] = new boss_room_state(room_data(index - 10, player_data(), this, 3));
        m_floorplans[m_current_world][index - 10] += 1;
    }
    if (fp[index + 10] == 1 || fp[index + 10] == 5)
    {
        m_worlds[m_current_world][index + 10] = new room_state(room_data(index + 10, player_data(), this, 1));
        m_floorplans[m_current_world][index + 10] += 1;
    }
    else if (fp[index + 10] == 3)
    {
        m_worlds[m_current_world][index + 10] = new boss_room_state(room_data(index + 10, player_data(), this, 1));
        m_floorplans[m_current_world][index + 10] += 1;
    }
}

bool world_generator::is_fully_explored()
{
    int sum = 0;
    for (int i = 0; i < m_floorplans[m_current_world].size(); i++)
    {
        sum += m_floorplans[m_current_world][i];
    }
    return sum >= (m_generators[m_current_world].room_count() * 2 + 2);
}