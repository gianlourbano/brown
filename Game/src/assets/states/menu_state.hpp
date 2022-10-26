#pragma once
#include "engine/brown.hpp"
#include "state_1.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
#include "assets/scripts/healthbar_controller.hpp"
#include "assets/scripts/AI.hpp"
#include <random>

#include "assets/test/tile_system.hpp"

#define TILES 14

brown::state_1 brown::state_1::m_state_1;
game_state game_state::m_game_state;

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
        set_win(brown::graphics::create_newwin(LINES, COLS, 0, 0));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        brain.register_component<tilemap>();

        tiles_system = tile_system::register_system(&brain);

        animation_system = brown::animation_system::register_system(&brain);
        scripts_system = brown::scripts_system::register_system(&brain);
        UI_system = brown::UI_system::register_system(&brain);
        render_system = brown::render_system::register_system(&brain);
        render_system->init();

        m_controller.init(&brain);

        std::string tilenames[TILES];
        for (int i = 0; i < TILES; i++)
        {
            tilenames[i] = "tile_" + std::to_string(i + 1);
        }
        ts = new tileset(TILES, tilenames);

        auto map = create_entity("map");
        vec2 map_size = {17, 8};
        int row, col;
        getmaxyx(win, row, col);

        offset.x = (col - map_size.x * TILE_SIZE) / 2;
        offset.y = (row - map_size.y * TILE_SIZE) / 2;
        if (offset.y < 7)
            offset.y = 7;
        map.add_component<transform>({offset, 0});
        tilemap &tm = map.add_component<tilemap>({ts, map_size.x, map_size.y});
        tm.load_from_file("tilemap_1");

        create_door(offset + vec2{5*TILE_SIZE, 0}, false, "1");
        create_door(offset + vec2{13*TILE_SIZE, 2*TILE_SIZE+2}, false, "2");
        // create_door({offset.x + 52, offset.y }, false, "3");

        auto pl = create_entity("player");
        pl.add_component<transform>({{offset.x + 35, offset.y + 7}, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({});

        auto bot1 = create_entity();
        bot1.add_component<transform>({offset + vec2{rand() % (map_size.x*TILE_SIZE), rand() % (map_size.y*TILE_SIZE)}, 1});
        
        brown::add_sprite({"4"}, "bot1");
        bot1.add_component<sprite>({{1, 1}, "bot1"});
        bot1.add_component<native_script>({}).bind<AI>();
        bot1.add_component<ui>({"Hello stranger!", 0, false, true});

        auto bot2 = create_entity();
        bot2.add_component<transform>({offset + vec2{rand() % (map_size.x*TILE_SIZE), rand() % (map_size.y*TILE_SIZE)}, 1});
        brown::add_sprite({"3"}, "bot2");
        bot2.add_component<sprite>({{1, 1}, "bot2"});
        bot2.add_component<native_script>({}).bind<AI>();
        bot2.add_component<ui>({"I see you!", 0, false, true});

        pl.add_component<native_script>({}).bind<player_controller>();

        auto hb = create_entity("healtbar");
        hb.add_component<transform>({{1, 2}, 1});
        hb.add_component<ui>({""});
        hb.add_component<native_script>({}).bind<healtbar_controller>();

        auto pl_bar = create_entity("power_level_bar");
        pl_bar.add_component<transform>({{1, 3}, 1});
        pl_bar.add_component<ui>({"Power level: ★ ★ ★ ★ ★"});

        auto key_c = create_entity("key_counter");
        key_c.add_component<transform>({{1, 4}, 1});
        key_c.add_component<ui>({"Keys: 🔑🗝"});

        brown::colors::add_custom_pair(COLOR_WHITE, 8);

        auto h_text = create_entity("h_text");
        h_text.add_component<transform>({0, 1});
        h_text.add_component<ui>({"Press 'h' to open the help menu"});
    }

    void resume() {}
    void pause() {}
    void cleanup() { delete ts; }

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

                break;
            case 'p':
                game->change_state(game_state::instance());
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
        wbkgdset(win, COLOR_PAIR(8));

        render_system->draw(win, &brain, Z_INDEX::Z_1);
        tiles_system->draw_tilemap(win, &brain);
        render_system->draw(win, &brain);
        UI_system->draw(win, &brain);
        doupdate();
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

    std::shared_ptr<tile_system> tiles_system;

    tileset *ts;

    vec2 offset;
    vec2 room_sprite_size = {71, 17};
};