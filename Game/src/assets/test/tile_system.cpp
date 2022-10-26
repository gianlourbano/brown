#include "tile_system.hpp"
#include "engine/core/ECS/components/transform.hpp"
#include "engine/graphics/window/window.hpp"

#include <unordered_map>

extern std::unordered_map<char, int> char_map;

std::shared_ptr<tile_system> tile_system::register_system(brown::brain *br)
{
    auto sys = br->register_system<tile_system>();
    signature signature;
    signature.set(br->get_component_type<tilemap>());
    signature.set(br->get_component_type<transform>());

    br->set_system_signature<tile_system>(signature);
    return sys;
}

void tile_system::init()
{
}

void tile_system::draw_tilemap(WINDOW *win, brown::brain *br)
{
    for (auto &e : m_entities)
    {
        auto &tm = br->get_component<tilemap>(e);
        auto &ts = br->get_component<transform>(e);
        for (int i = 0; i < tm.m_x; i++)
        {
            for (int j = 0; j < tm.m_y; j++)
            {
                if (tm.m_data.at(i, j) != -1)
                    print_tile(win, tm.m_tileset->operator[](tm.m_data.at(i, j)), vec2(ts.position.x + i * TILE_SIZE, ts.position.y + j * TILE_SIZE));
            }
        }
    }
}