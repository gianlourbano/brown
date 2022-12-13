#pragma once
#include "engine/brown.hpp"
#include "assets/test/tile_system.hpp"

class game_state : public brown::state
{

public:

    void init(brown::engine *game)
    {
        set_win(brown::graphics::create_newwin(LINES/2, COLS/2,LINES/4, COLS/4));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();
        scripts_system = brown::scripts_system::register_system(&brain);
        UI_system = brown::UI_system::register_system(&brain);
        render_system = brown::render_system::register_system(&brain);
        render_system->init();

        m_controller.init(&brain);
    
    }

    void resume() {}
    void pause() {}
    void cleanup() {}
    void draw(brown::engine *game)
    {
        werase(win);
        wbkgdset(win, COLOR_PAIR(8));
        box(win, 0, 0);
        render_system->draw(win, &brain);
        UI_system->draw(win, &brain);
        wrefresh(win);
    }
    void handle_events(brown::engine *game)
    {
    }
    void update(brown::engine *game)
    {
    }
    static game_state *instance()
    {
        return &m_game_state;
    }

protected:
    game_state() {}

private:
    static game_state m_game_state;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
    std::shared_ptr<brown::UI_system> UI_system;
};