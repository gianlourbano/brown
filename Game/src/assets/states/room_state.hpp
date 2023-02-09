#pragma once
#include "engine/brown.hpp"

#include "assets/test/tile_system.hpp"
#include "assets/items/items.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/healthbar_controller.hpp"
#include "assets/scripts/scriptable_enemy.hpp"
#include "assets/scripts/ranged_enemy.hpp"
#include "assets/scripts/inventory_renderer.hpp"
#include "assets/scripts/score_controller.hpp"

#include "assets/test/tile_system.hpp"
#include "assets/items/items.hpp"

#include "room_state.hpp"
#include "assets/map_gen/level_generator.hpp"

#include "engine/std/vector.hpp"
#include "assets/map_gen/world_generator.hpp"

#define TILES 15

struct room_data
{
    int id;

    // player data
    int player_health;
    int player_max_health;
    int score;
    inventory *player_inventory;
    world_generator *world_gen;

    // room data
    int direction;

    room_data() {}
    room_data(int id, int player_health, int player_max_health,int score, inventory *player_inventory, world_generator *world_gen, int direction)
    {
        this->id = id;
        this->player_health = player_health;
        this->player_max_health = player_max_health;
        this->score = score;
        this->player_inventory = player_inventory;
        this->world_gen = world_gen;
        this->direction = direction;
    }
};

class room_state : public brown::state
{

public:
    room_state() {}
    room_state(room_data data) : data(data) {}

    void inject_data(int dir)
    {
        this->data.direction = dir;
    }

    void generate_doors(tilemap &tm);

    void init(brown::engine *game)
    {
        m_game = game;

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

        // ROOM INITIALIZATION
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

        offset.x = (col - map_size.x * TILE_SIZE) / 2;
        offset.y = (row - map_size.y * TILE_SIZE) / 2;
        if (offset.y < 7)
            offset.y = 7;
        map.add_component<transform>({offset, 0});
        tilemap &tm = map.add_component<tilemap>({ts, map_size.x, map_size.y});
        tm.load_from_file("tilemap_1");

        data.world_gen->generate_neighbouring_rooms(data.id);
        generate_doors(tm);

        // PLAYER INITIALIZATION
        auto pl = create_entity("player");

        vec2 pos = offset;
        switch (data.direction)
        {
        case 1:
        {
            pos += vec2(8 * TILE_SIZE + 2, 4);
            break;
        }
        case 2:
        {
            pos += vec2(16 * TILE_SIZE, 2 * TILE_SIZE + 3);
            break;
        }
        case 3:
        {
            pos += vec2(8 * TILE_SIZE + 2, 5 * TILE_SIZE + 2);
            break;
        }
        case 4:
        {
            pos += vec2(3, 2 * TILE_SIZE + 3);
            break;
        }
        case 0:
        {
            pos = vec2(COLS / 2, LINES / 2);
            break;
        }
        }

        pl.add_component<transform>({pos, 1});
        pl.add_component<sprite>({{2, 2}, "sprite2"});
        pl.add_component<animator_controller>({});
        pl.add_component<native_script>({}).bind<player_controller>(data.player_health);

        player_controller *pl_controller = dynamic_cast<player_controller *>(pl.get_component<native_script>().instance);
        // pl_controller->m_inventory = *data.player_inventory;

        // UI
        // auto inventory = create_entity("inventory_manager");
        // inventory.add_component<native_script>({}).bind<inventory_renderer>();

        auto hb = create_entity("healtbar");
        hb.add_component<transform>({{1, 2}, 1});
        hb.add_component<ui>({""});
        hb.add_component<native_script>({}).bind<healtbar_controller>();

        auto pl_bar = create_entity("power_level_bar");
        pl_bar.add_component<transform>({{1, 3}, 1});
        pl_bar.add_component<ui>({"Power level: ★ ★ ★ ★ ★"});

        auto key_c = create_entity("id");
        key_c.add_component<transform>({{1, 4}, 1});
        key_c.add_component<ui>({"ROOM_ID: " + std::to_string(data.id)});

        auto sb = create_entity("scorebar");
        sb.add_component<transform>({{1, 5}, 1});
        sb.add_component<ui>({""});
        sb.add_component<native_script>({}).bind<score_controller>();

        auto h_text = create_entity("h_text");
        h_text.add_component<transform>({0, 1});
        h_text.add_component<ui>({"Press 'h' to open the help menu"});

        auto inv = create_entity("inv");
        inv.add_component<transform>({{1, 7}});
        inv.add_component<ui>({"Inventory"});

        initialized = true;
        LOG("INIT");
    }

    void cleanup() {}
    void pause() { m_pause = true; }
    void resume()
    {
        LOG("RESUME");
        m_pause = false;
        transform *ts = &find_entity("player").get_component<transform>();
        vec2 pos = offset;
        switch (data.direction)
        {
        case 3:
        {
            pos += vec2(8 * TILE_SIZE + 2, 4);
            break;
        }
        case 4:
        {
            pos += vec2(16 * TILE_SIZE, 2 * TILE_SIZE + 3);
            break;
        }
        case 1:
        {
            pos += vec2(8 * TILE_SIZE + 2, 5 * TILE_SIZE + 2);
            break;
        }
        case 2:
        {
            pos += vec2(3, 2 * TILE_SIZE + 3);
            break;
        }
        case 0:
        {
            pos = vec2(COLS / 2, LINES / 2);
            break;
        }
        }

        ts->position = pos;
    }
    void handle_events(brown::engine *game)
    {
        if (!m_pause)
        {
            brown::get_keyboard_input(win);
            if (brown::KEY_PRESSED != ERR)
            {
                switch (brown::KEY_PRESSED)
                {
                case 'm':
                    // m_controller.LOG_ENTITIES();
                    break;
                case 'c':
                    game->pop_state();
                    break;
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

            world_generator::floorplan floorplan = data.world_gen->get_current_floorplan();
            int y = 1, x = COLS - 15;
            for (int i = 0; i < 100; i++)
            {
                if (i == data.id)
                    brown::graphics::mvwaddchcolors(win, y, x, 17, 'o');
                else if (floorplan[i])
                    brown::graphics::mvwaddchcolors(win, y, x, 16, 'x');

                if (i % 10 == 0)
                {
                    y++;
                    x -= 10;
                }

                x++;
            }
        }
    }

    int last_entered = 0;

private:
    std::shared_ptr<brown::animation_system> animation_system;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
    std::shared_ptr<brown::UI_system> UI_system;

    std::shared_ptr<tile_system> tiles_system;

    vec2 offset = 0;
    bool m_pause = false;

    tileset *ts = nullptr;

    int frame_passed = 0;

    

    room_data data;
};