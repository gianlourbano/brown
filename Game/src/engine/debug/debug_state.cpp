#include "debug_state.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include "graphics/window/window.hpp"

#include <ncurses.h>

extern std::vector<std::string> GLOBAL_SPRITES_paths;
extern std::unordered_map<std::string, std::vector<std::string>> GLOBAL_SPRITES;

namespace brown::debug
{
    debug_state debug_state::m_debug_state;

    void debug_state::init(brown::engine *game)
    {
        set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);
    }

    void debug_state::cleanup(){};
    void debug_state::pause(){};
    void debug_state::resume(){};

    void debug_state::draw(brown::engine *game)
    {
        mvwprintw(win, 2, 2, "current sprites loaded: %d\n", GLOBAL_SPRITES_paths.size());
        for (auto &str : GLOBAL_SPRITES_paths)
        {
            wprintw(win, "\t%s\n", str.c_str());
        }

        wprintw(win,"current sprites loaded in game: %d\n\t", GLOBAL_SPRITES.size());
    }
    void debug_state::handle_events(brown::engine *game)
    {
        int ch = wgetch(win);
        {
            if (ch != ERR)
            {
                switch (ch)
                {
                case KEY_F(1):
                    game->pop_state();
                    break;
                case 'p':
                    game->quit();
                    break;
                }
            }
        }
    }
    void debug_state::update(brown::engine *game) {}
}
