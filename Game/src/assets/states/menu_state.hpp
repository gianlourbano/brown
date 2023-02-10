#pragma once
#include "engine/brown.hpp"
#include "game_state.hpp"
#include "help_state.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/door_controller.hpp"
#include "assets/scripts/healthbar_controller.hpp"
#include "assets/scripts/NPC.hpp"
#include "assets/scripts/scriptable_enemy.hpp"
#include "assets/scripts/ranged_enemy.hpp"
#include "assets/scripts/logo_controller.hpp"
#include "assets/scripts/score_controller.hpp"
#include <random>
#include "assets/scripts/inventory_renderer.hpp"

#include "assets/test/tile_system.hpp"
#include "assets/items/items.hpp"

#include "room_state.hpp"
#include "assets/map_gen/level_generator.hpp"
#include "assets/map_gen/world_generator.hpp"

#include "engine/std/vector.hpp"

#define TILES 15

int frame_passed = 0;

game_state game_state::m_game_state;
help_state help_state::m_help_state;

class menu_state : public brown::state
{
public:
    void QuitHandler(brown::event &e)
    {
        m_game->quit();
    }

    void create_door(vec2 pos,door_data data, bool vertical = true, std::string name = "1")
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

        door.add_component<native_script>({}).bind<door_controller>(data);
    }

    void plain_text(std::string text, int x, int y)
    {
        mvwprintw(win, y, x, text.c_str());
    }

    void init(brown::engine *game)
    {
        m_game = game;
        // state window initialization
        srand(time(NULL));
        set_win(brown::graphics::create_newwin(LINES, COLS, 0, 0));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        add_event_listener(METHOD_LISTENER(Events::Window::QUIT, "Quit", menu_state::QuitHandler));

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
        vec2 map_size = {17, 6};
        int row, col;
        getmaxyx(win, row, col);

        auto logo = create_entity("logo");
        logo.add_component<sprite>({0, "logo"});
        logo.add_component<transform>({vec2((col / 2) - 29, -10)});
        logo.add_component<native_script>({}).bind<logo_controller>();

        offset.x = (col - map_size.x * TILE_SIZE) / 2;
        offset.y = (row - map_size.y * TILE_SIZE) / 2;
        if (offset.y < 7)
            offset.y = 7;
        map.add_component<transform>({offset, 0});
        tilemap &tm = map.add_component<tilemap>({ts, map_size.x, map_size.y});
        tm.load_from_file("tilemap_1");

        auto pl = create_entity("player");
        pl.add_component<transform>({{offset.x + 35, offset.y + 7}, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({});
        pl.add_component<native_script>({}).bind<player_controller>(10);

        // world generation
        m_world_generator.generate_new_world();
        create_door(offset + vec2{8 * TILE_SIZE, 0},door_data( m_world_generator.get_room_for_current_world(45),nullptr, 45, false, false) ,false, "1");
        tm.set_tile(3, 0, 8);

        // room generation
        // auto bot1 = create_entity();
        // bot1.add_component<transform>({offset + vec2{rand() % (map_size.x * TILE_SIZE), rand() % (map_size.y * TILE_SIZE)}, 1});

        // brown::add_sprite({"4"}, "bot1");
        // bot1.add_component<sprite>({{1, 1}, "bot1"});
        // bot1.add_component<native_script>({}).bind<NPC>();
        // bot1.add_component<ui>({""});

        // auto bot2 = create_entity();
        // bot2.add_component<transform>({offset + vec2{rand() % (map_size.x * TILE_SIZE), rand() % (map_size.y * TILE_SIZE)}, 1});
        // brown::add_sprite({"a"}, "bot2");
        // bot2.add_component<sprite>({{1, 1}, "bot2"});
        // bot2.add_component<native_script>({}).bind<scriptable_enemy>();
        // bot2.add_component<ui>({"", 0, true, true});

        // auto bot3 = create_entity();
        // bot3.add_component<transform>({offset + vec2{rand() % (map_size.x * TILE_SIZE), rand() % (map_size.y * TILE_SIZE)}, 1});
        // brown::add_sprite({"a"}, "bot3");
        // bot3.add_component<sprite>({{1, 1}, "bot3"});
        // bot3.add_component<native_script>({}).bind<ranged_enemy>();
        // bot3.add_component<ui>({"", 0, true, true});

        // auto pot = create_entity("potion1");
        // pot.add_component<transform>({{40, 16}});
        // pot.add_component<sprite>({{1, 1}, "bot2"});
        // pot.add_component<native_script>({}).bind<potion>(4);

        // auto pot1 = create_entity("potion2");
        // pot1.add_component<transform>({{50, 16}});
        // pot1.add_component<sprite>({{1, 1}, "bot2"});
        // pot1.add_component<native_script>({}).bind<potion>(4);

        // auto h_text = create_entity("h_text");
        // h_text.add_component<transform>({0, 1});
        // h_text.add_component<ui>({"Press 'h' to open the help menu"});
        auto inventory = create_entity("inventory_manager");
        inventory.add_component<native_script>({}).bind<inventory_renderer>();

        auto hb = create_entity("healtbar");
        hb.add_component<transform>({{1, 2}, 1});
        hb.add_component<ui>({""});
        hb.add_component<native_script>({}).bind<healtbar_controller>();

        auto sb = create_entity("scorebar");
        sb.add_component<transform>({{1, 5}, 1});
        sb.add_component<ui>({""});
        sb.add_component<native_script>({}).bind<score_controller>();

        auto pl_bar = create_entity("power_level_bar");
        pl_bar.add_component<transform>({{1, 3}, 1});
        pl_bar.add_component<ui>({"Power level: ★ ★ ★ ★ ★"});

        auto key_c = create_entity("key_counter");
        key_c.add_component<transform>({{1, 4}, 1});
        key_c.add_component<ui>({"Keys: 🔑🗝"});

        auto h_text = create_entity("h_text");
        h_text.add_component<transform>({0, 1});
        h_text.add_component<ui>({"Press 'h' to open the help menu"});

        auto inv = create_entity("inv");
        inv.add_component<transform>({{1,7}});
        inv.add_component<ui>({"Inventory"});
    }

    void resume() { m_pause = false; }
    void pause() { m_pause = true; }
    void cleanup()
    {
        delete ts;

        for (int i = 0; i < 100; i++)
            if (room_states[i])
                delete room_states[i];
    }

    // queste tre vengono eseguite in ordine e
    // fanno esattamente quello che c'è scritto
    void handle_events(brown::engine *game)
    {
        if (terminate)
            game->quit();

        if (!m_pause)
        {
            brown::get_keyboard_input(win);
            if (brown::KEY_PRESSED != ERR)
            {
                switch (brown::KEY_PRESSED)
                {
                case 'm':
                    m_controller.LOG_ENTITIES();
                    break;
                case 'c':
                    UI_system->LOG_COLORS();
                    break;
                case 'h':
                {
                    game->push_state(help_state::instance());
                    break;
                }
                case 'l':
                    game->quit();
                    break;
                case 'p':
                    m_pause = true;
                }
            }
        }
        else
        {
            brown::get_keyboard_input(win);
            if (brown::KEY_PRESSED != ERR && brown::KEY_PRESSED == 'p')
            {
                m_pause = false;
            }
        }
    }
    void update(brown::engine *game)
    {
        if (!m_pause)
        {
            frame_passed++;
            animation_system->update(&brain, frame_passed);
            if (frame_passed > FPS)
                frame_passed = 0;
            scripts_system->update(this);
            m_controller.empty_to_be_deleted();
        }
    }
    void draw(brown::engine *game)
    {
        if (!m_pause)
        {
            werase(win);
            wbkgdset(win, COLOR_PAIR(8));

            render_system->draw(win, &brain, Z_INDEX::Z_1);
            tiles_system->draw_tilemap(win, &brain);
            render_system->draw(win, &brain);
            UI_system->draw(win, &brain);
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
    std::shared_ptr<brown::UI_system> UI_system;

    std::shared_ptr<tile_system> tiles_system;

    tileset *ts = nullptr;

    vec2 offset;

    bool m_pause = false;

    // WORLD GENERARATION
    brown::dt::vector<int> floorplan;
    mat<room_state *> room_states = mat<room_state *>(10, 10);

    world_generator m_world_generator;
};