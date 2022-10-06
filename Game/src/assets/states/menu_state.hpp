#pragma once
#include "engine/brown.hpp"
#include "state_1.hpp"

brown::state_1 brown::state_1::m_state_1;

class menu_state : public brown::state
{

public:
    void init(brown::engine *game)
    {
        // state window initialization

        set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        render_system = brown::render_system::register_system(&brain);
        render_system->init();
        /* inserire sistemi che si intendono usare, così:
            system = system::register(&brain);
        */

        /*
             gestisci entità.
        */
    }

    void resume() {}
    void pause() {}
    void cleanup() {}

    // queste tre vengono eseguite in ordine e
    // fanno esattamente quello che c'è scritto
    void update(brown::engine *game) {}
    void handle_events(brown::engine *game)
    {
        brown::get_keyboard_input(win);
        if (brown::KEY_PRESSED != ERR)
        {
            switch (brown::KEY_PRESSED)
            {
            case 'p':
                game->change_state(brown::state_1::instance());
                break;
            case 'l':
                game->quit();
                break;
            }
        }
    }
    void draw(brown::engine *game)
    {
        werase(win);
        werase(game->get_std_screen());
        box(win, 0, 0);

        render_system->draw(win, &brain);
    }

    static menu_state *instance()
    {
        return &m_menu_state;
    }

protected:
    menu_state() {}

private:
    std::shared_ptr<brown::render_system> render_system;

    static menu_state m_menu_state;
};