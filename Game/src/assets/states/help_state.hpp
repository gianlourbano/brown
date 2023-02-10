#pragma once
#include "engine/brown.hpp"
#include "assets/test/tile_system.hpp"

#include "assets/map_gen/level_generator.hpp"
#include "assets/states/game_state.hpp"

class help_state : public brown::state
{
public:
    void init(brown::engine *game)
    {
        set_win(brown::graphics::create_newwin(LINES, COLS,0, 0));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();
        brain.register_component<tilemap>();
        tile_system_ = tile_system::register_system(&brain);
        scripts_system = brown::scripts_system::register_system(&brain);
        UI_system = brown::UI_system::register_system(&brain);
        render_system = brown::render_system::register_system(&brain);
        render_system->init();

        m_controller.init(&brain);
        
        auto line_1 = create_entity("line_1");
        line_1.add_component<transform>({vec2(0)});
        line_1.add_component<ui>({"Welcome,\nuse\n    W\n   A D to move\n    S\nF1/Ctrl+c to quit\nP to pause\nT to fire projectiles\n... "});

        level_generator generator = level_generator(1);
        generator.generate();

        auto floorplan = generator.get_floorplan();

        std::string tilenames[] =  {"map_1", "map_2"};
        ts = new tileset(2, tilenames);

        auto map = create_entity("map");
        map.add_component<transform>({vec2(0)});
        tilemap &tm = map.add_component<tilemap>({ts, 10, 10});
        tm.m_data.set_all(floorplan);
    }

    void resume() {}
    void pause() {}
    void cleanup() {}
    void draw(brown::engine *game)
    {
        werase(win);
        //wbkgdset(win, COLOR_PAIR(8));
        box(win, 0, 0);
        tile_system_->draw_tilemap(win, &brain);
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
            case 'g':
                game->push_state(game_state::instance());
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
    std::shared_ptr<tile_system> tile_system_;

    tileset *ts = nullptr;
};