#pragma once
#include "engine/brown.hpp"
#include "state_1.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
brown::state_1 brown::state_1::m_state_1;

class menu_state : public brown::state
{

public:
 void create_door(vec2 pos, bool vertical = true)
        {
            auto door = create_entity("door1");
            door.add_component<transform>({pos});
            door.add_component<sprite>({{3, 2}, vertical ? "door1" : "door2"});
            door.add_component<animator_controller>({}).add_anim("open", {vertical ? 4 : 6, false, 0, false, vertical ? 20 : 10, {0, 0}, vertical ? "animated_vertical_door" : "animated_horizontal_door", true});
            door.add_component<native_script>({}).bind<door_controller>();
        }
    void init(brown::engine *game)
    {
        // state window initialization

        set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        animation_system = brown::animation_system::register_system(&brain);
        scripts_system = brown::scripts_system::register_system(&brain);

        render_system = brown::render_system::register_system(&brain);
        render_system->init();

        m_controller.init(&brain);

        auto room = create_entity("menu");
        room.add_component<transform>({{0, 0}, 0});
        room.add_component<sprite>({{71, 17}, "menu"});

        /*create_door({160, 0}, false);
        create_door({320, 0}, false);
        create_door({480, 0}, false);
        */
        auto pl = create_entity("player");
        pl.add_component<transform>({{4, 4}, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({}).add_anim("idle", {5, false, 0, false, 5, {2, 2}, "animated1"});
        pl.add_component<native_script>({}).bind<player_controller>();
    }

    void resume() {}
    void pause() {}
    void cleanup() {}

    // queste tre vengono eseguite in ordine e
    // fanno esattamente quello che c'è scritto
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
    void update(brown::engine *game) {
                frame_passed++;
                animation_system->update(&brain, frame_passed);
                if (frame_passed > FPS)
                    frame_passed = 0;
                scripts_system->update(this);
                m_controller.empty_to_be_deleted();
            
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
    static menu_state m_menu_state;
    std::shared_ptr<brown::animation_system> animation_system;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
};