#pragma once
#include "engine/brown.hpp"
#include "state_1.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
#include <random>
#include <time.h>
brown::state_1 brown::state_1::m_state_1;

class menu_state : public brown::state
{

public:
    void create_door(vec2 pos, bool vertical = true, std::string name = "1")
    {
        animation opened = {
            vertical ? "animated_vertical_door" : "animated_horizontal_door",
            {0, 0},
            vertical ? 4 : 6,
            vertical ? 20 : 10,
            false,
            true};

        animation closed = {
            vertical ? "animated_vertical_door_c" : "animated_horizontal_door_c",
            {0, 0},
            vertical ? 4 : 6,
            vertical ? 20 : 10,
            false,
            true};

        auto door = create_entity("door_" + name);
        door.add_component<transform>({pos});
        door.add_component<sprite>({{3, 2}, vertical ? "door1" : "door2"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("close", closed);
        anim->add_anim("open", opened);

        door.add_component<native_script>({}).bind<door_controller>();
    }
    void init(brown::engine *game)
    {
        // state window initialization
        srand(time(NULL));
        set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        animation_system = brown::animation_system::register_system(&brain);
        scripts_system = brown::scripts_system::register_system(&brain);
        UI_system = brown::UI_system::register_system(&brain);
        render_system = brown::render_system::register_system(&brain);
        render_system->init();

        m_controller.init(&brain);

        auto room = create_entity("menu");
        auto room_spr = room.add_component<sprite>({{71, 17}, "menu"});
        
        int row, col;
        getmaxyx(win, row, col);
        vec2 offset = {(col - room_spr.size.x)/2, (row - room_spr.size.y)/2};
        
        room.add_component<transform>({offset, 0});

        create_door(vec2{33, 0} + offset, false, "1");
        create_door(vec2{52, 0} + offset, false, "2");
        create_door(vec2{15, 0} + offset, false, "3");

        auto pl = create_entity("player");
        pl.add_component<transform>({vec2{3, 12} + offset, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({});
        pl.add_component<native_script>({}).bind<player_controller>();

        auto text1 = create_entity("text1");
        text1.add_component<transform>({{3, 3}, 1});
        text1.add_component<ui>({"this is text"});
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
            case 'm':
                m_controller.LOG_ENTITIES();
                break;
            case 'u':
                find_entity("door_1").get_component<animator_controller>().play_reversed("open");
                break;
            case 'i':
                find_entity("door_1").get_component<animator_controller>().play("open");
                break;
            case 'p':
                game->change_state(brown::state_1::instance());
                break;
            case 'l':
                game->quit();
                break;
            }
        }
    }
    void update(brown::engine *game)
    {
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

        UI_system->draw(win, &brain);
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
    std::shared_ptr<brown::UI_system> UI_system;
};