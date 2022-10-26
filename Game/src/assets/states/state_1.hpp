#pragma once
#include "engine/brown.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
#include "game_state.hpp"

//game_state game_state::m_game_state;
int frame_passed = 0;
extern int FPS;

namespace brown
{
    class state_1 : public state
    {
    public:
        void create_door(vec2 pos, bool vertical = true)
        {
            animation opened = {
            vertical ? "animated_vertical_door" : "animated_horizontal_door",
            {0, 0},
            vertical ? 4 : 6,
            vertical ? 20 : 10,
            false,
            false
        };
            auto door = create_entity("door1");
            door.add_component<transform>({pos});
            door.add_component<sprite>({{3, 2}, vertical ? "door1" : "door2"});
            door.add_component<animator_controller>({}).add_anim("open", opened);
            door.add_component<native_script>({}).bind<door_controller>();
        }

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

            auto room = create_entity("room");
            room.add_component<transform>({{0, 0}, 0});
            room.add_component<sprite>({{71, 17}, "room1"});

            create_door({69, 5});
            create_door({20, 0}, false);
            
            auto pl = create_entity("player");
            pl.add_component<transform>({{4, 4}, 1});
            pl.add_component<sprite>({{2, 2}, "sprite2"});
            pl.add_component<animator_controller>({});
            pl.add_component<native_script>({}).bind<player_controller>();
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
                    //game->push_state(brown::debug::debug_state::instance());
                    break;
                    
                }
            }
        };

        void update(engine *game)
        {
            if (!pause_fl)
            {
                frame_passed++;
                animation_system->update(&brain, frame_passed);
                if (frame_passed > FPS)
                    frame_passed = 0;
                scripts_system->update(this);
                m_controller.empty_to_be_deleted();
            }
        };

        void draw(engine *game)
        {
            if (!pause_fl)
            {
                werase(win);
                werase(game->get_std_screen());
                box(win, 0, 0);

                render_system->draw(win, &brain);
            }
        };

        static state_1 *instance()
        {
            return &m_state_1;
        }

    protected:
        state_1() {}

    private:
        bool pause_fl = false;
        static state_1 m_state_1;
        std::shared_ptr<brown::animation_system> animation_system;
        std::shared_ptr<brown::render_system> render_system;
        std::shared_ptr<brown::scripts_system> scripts_system;
    };
}