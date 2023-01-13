#pragma once
#include "engine/brown.hpp"
#include "assets/scripts/pause_screen.hpp"
namespace brown
{
    class state_2 : public state
    {
    public:
        void init(brown::engine *game)
        {
            set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
            brown::graphics::start_curses_flags(win);
            game->set_current_screen(win);

            brain.init();

            animation_system = animation_system::register_system(&brain);
            scripts_system = scripts_system::register_system(&brain);

            render_system = render_system::register_system(&brain);
            render_system->init();

            m_controller.init(&brain);

            auto menu = create_entity("menu");
            room.add_component<transform>({{10,10}, 0});
            room.add_component<sprite>({{71, 17}, "pause"});
        };

        void cleanup(){};
        void pause() { pause_fl = true; };
        void resume() { pause_fl = false; };

        void handle_events(engine *game)
        {
            brown::get_keyboard_input(win);
            if (brown::KEY_PRESSED != ERR)
            {
                switch (brown::KEY_PRESSED)
                {
                case 'p':
                    pause_fl = !pause_fl;
                    break;
                case 'l':
                    game->quit();
                    break;
                case KEY_F(1):
                    game->push_state(brown::debug::debug_state::instance());
                    game->push_state()
                    break;
                }
            }
        };

        void update(engine *game)
        {
        };

        void draw(engine *game)
        {
                werase(win);
                werase(game->get_std_screen());
                box(win, 0, 0);
        };

        static state_2 *instance()
        {
            return &m_state_2;
        }

    protected:
        state_2() {}

    private:
        bool pause_fl = false;
        static state_2 m_state_2;
        std::shared_ptr<brown::animation_system> animation_system;
        std::shared_ptr<brown::render_system> render_system;
        std::shared_ptr<brown::scripts_system> scripts_system;
    };
}