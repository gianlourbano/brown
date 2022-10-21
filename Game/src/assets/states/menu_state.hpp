#pragma once
#include "engine/brown.hpp"
#include "state_1.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
brown::state_1 brown::state_1::m_state_1;

class menu_state : public brown::state
{

public:
    void create_door(vec2 pos, bool vertical = true, std::string name = "1")
    {
        animation opened = {
            vertical ? "animated_vertical_door" : "animated_horizontal_door",
            {0, 0},
            vertical ? 4 : 5,
            vertical ? 20 : 10,
            false,
            true
        };

        auto door = create_entity("door_" + name);
        door.add_component<transform>({pos});
        door.add_component<sprite>({{3, 2}, vertical ? "door1" : "door2"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>(); 
        // anim->add_anim("close", closed);
        anim->add_anim("open", opened);

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

        create_door({15, 1}, false, "1");
        create_door({33, 1}, false, "2");
        create_door({52, 1}, false, "3");
        

        auto pl = create_entity("player");
        pl.add_component<transform>({{35, 7}, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({});
        pl.add_component<native_script>({}).bind<player_controller>();

        this->d1 =find_entity("door_1").get_component<transform>().position;
        this->d2 =find_entity("door_2").get_component<transform>().position;
        this->d3 =find_entity("door_3").get_component<transform>().position;
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
        this->pp = find_entity("player").get_component<transform>().position;
        frame_passed++;
        animation_system->update(&brain, frame_passed);
        if (frame_passed > FPS)
            frame_passed = 0;
        scripts_system->update(this);
        m_controller.empty_to_be_deleted();
    }
    void draw(brown::engine *game)
    {
        if(pp.x>=d1.x&&pp.x<=d1.x+4&&pp.y==d1.y){
            game->push_state(brown::state_1::instance());
        }else if(pp.x>=d2.x&&pp.x<=d2.x+4&&pp.y==d2.y)
        {
            
        }else if(pp.x>=d3.x&&pp.x<=d3.x+4&&pp.y==d3.y)
        {
            game->quit();
        }else{
        werase(win);
        werase(game->get_std_screen());
        box(win, 0, 0);
        render_system->draw(win, &brain);
        }
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
    vec2 pp, d1,d2,d3;
};