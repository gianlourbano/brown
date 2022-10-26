#pragma once
#include "engine/core/ECS/system.hpp"
#include "engine/core/brain.hpp"
#include <ncurses.h>
#include "tileset.hpp"

class tile_system : public brown::system
{
public:
    static std::shared_ptr<tile_system> register_system(brown::brain *br);
    
    void init();
    void draw_tilemap(WINDOW* win, brown::brain* br);
};