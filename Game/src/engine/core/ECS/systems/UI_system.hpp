#pragma once
#include "engine/core/ECS/system.hpp"
#include "engine/core/brain.hpp"
#include "engine/core/ECS/components/ui.hpp"
#include <ncurses.h>

namespace brown
{
    class UI_system : public brown::system
    {
    public:
        static std::shared_ptr<UI_system> register_system(brown::brain* br);

        void init();
        void draw(WINDOW *win, brain *br);
    };
}