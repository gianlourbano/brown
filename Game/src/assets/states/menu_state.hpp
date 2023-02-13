#pragma once
#include "engine/brown.hpp"
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

#define TILES 30

int frame_passed = 0;

class menu_state : public brown::state
{
public:
    void QuitHandler(brown::event &e)
    {
        m_game->quit();
    }

    void create_door(vec2 pos, door_data data, bool vertical = true, std::string name = "1")
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
        pl.add_component<native_script>({}).bind<player_controller>(player_data(&m_inventory));

        // world generation
        m_world_generator.generate_new_world(player_data(&m_inventory));
        create_door(offset + vec2{8 * TILE_SIZE + 1, 1}, door_data(m_world_generator.get_room_for_current_world(45), nullptr, 45, false, false), false, "1");
        tm.set_tile(3, 0, 8);

        // UI

        auto help_text = create_entity("help_text");
        help_text.add_component<transform>({vec2(2, LINES - 5)});
        help_text.add_component<ui>({"Press I to open inventory mode!\n  Press T to shoot a bullet!\n  Press E to interact with the world!\n  Move around with WASD!"});

        auto arrow = create_entity("arrow");
        arrow.add_component<transform>({offset + vec2{10 * TILE_SIZE, 2}});
        arrow.add_component<ui>({"Play"});

        auto npc1 = create_entity("npc1");
        npc1.add_component<transform>({get_valid_position()});
        npc1.add_component<sprite>({1, "sprite2"});
        npc1.add_component<ui>({"", {0, 1}, true, false});
        npc1.add_component<native_script>({}).bind<NPC>();

        auto npc2 = create_entity("npc2");
        npc2.add_component<transform>({get_valid_position()});
        npc2.add_component<sprite>({1, "sprite2"});
        npc2.add_component<ui>({"", {0, 1}, true, false});
        npc2.add_component<native_script>({}).bind<NPC>();
    }

    void resume() { m_pause = false; }
    void pause() { m_pause = true; }
    void cleanup()
    {
        delete ts;
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
                case 'l':
                    game->quit();
                    break;
                case 'p':
                    m_pause = true;
                }
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

    vec2 get_valid_position()
    {
        vec2 pos = offset;

        chtype ch;
        do
        {
            pos = offset + vec2{3 + rand() % ((map_size.x - 2) * TILE_SIZE), 3 + rand() % ((map_size.y - 2) * TILE_SIZE)};
            ch = mvwinch(win, pos.y, pos.x) & A_CHARTEXT;
        } while (ch != ' ');

        return pos;
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

    vec2 offset = 0;
    vec2 map_size = {17, 6};

    bool m_pause = false;

    // WORLD GENERARATION
    world_generator m_world_generator;

    inventory m_inventory;
};