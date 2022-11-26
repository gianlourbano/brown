#pragma once
#include "engine/brown.hpp"
#include "assets/test/tile_system.hpp"

class help_state : public brown::state
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
        
        auto line_1 = create_entity("line_1");
        line_1.add_component<transform>({vec2(0)});
        line_1.add_component<ui>({"Help Menu"});
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
        brown::get_keyboard_input(win);
        if (brown::KEY_PRESSED != ERR)
        {
            switch (brown::KEY_PRESSED)
            {
            case 'h':
                game->pop_state();
                break;
            
            case 'm':
                m_controller.LOG_ENTITIES();
                break;
            }
        }
    }
    void update(brown::engine *game)
    {
    }
    static help_state *instance()
    {
        return &m_help_state;
    }

protected:
    help_state() {}

private:
    static help_state m_help_state;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
    std::shared_ptr<brown::UI_system> UI_system;
};