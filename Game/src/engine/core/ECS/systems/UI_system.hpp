#pragma once
#include "engine/core/ECS/system.hpp"
#include "engine/core/brain.hpp"
#include "engine/core/ECS/components/ui.hpp"
#include <ncurses.h>
#include <map>

namespace brown
{
    class UI_system : public brown::system
    {
    public:
        static std::shared_ptr<UI_system> register_system(brown::brain* br);

        void init();
        void draw(WINDOW *win, brain *br);
        void cleanup(brain *br);

        void LOG_COLORS();

    private:
        int m_step = 0;
        std::map<short, short> m_pairs{};
    };
}