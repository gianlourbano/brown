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
#include "assets/scripts/boss.hpp"

#include "assets/test/tile_system.hpp"
#include "assets/items/items.hpp"

#include "room_state.hpp"
#include "assets/map_gen/level_generator.hpp"

#include "engine/std/vector.hpp"
#include "assets/map_gen/world_generator.hpp"

#define TILES 30  

struct room_data
{
    int id = -1;

    // player data
    int player_health = 10;
    int player_max_health = 10;
    bool key = false;
    int score = 0;
    inventory *player_inventory = nullptr;
    world_generator *world_gen = nullptr;

    // room data
    int direction = 0;

    room_data() {}
    room_data(int id, int player_health, int player_max_health, bool key,int score, inventory *player_inventory, world_generator *world_gen, int direction)
    {
        this->id = id;
        this->player_health = player_health;
        this->player_max_health = player_max_health;
        this->key=key;
        this->score = score;
        this->player_inventory = player_inventory;
        this->world_gen = world_gen;
        this->direction = direction;
    }
};

class room_state : public brown::state
{

public:
    room_state() = delete;
    room_state(room_data data)
    {
        this->data = data;
    }
    void key_changed(){
        data.key = true;
    }
    void health_changed(brown::event &e)
    {
        data.player_health = e.get_param<int>(Events::Player::Health::HEALTH);
    }

    void score_changed(brown::event &e)
    {
        data.score = e.get_param<int>(Events::Player::Score::SCORE);
    }

    room_data *get_data() { return &data; }

    void generate_doors(tilemap &tm);

    void init(brown::engine *game)
    {
        m_game = game;

        set_win(brown::graphics::create_newwin(LINES, COLS, 0, 0));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        add_event_listener(METHOD_LISTENER(Events::Player::HEALTH, "room", room_state::health_changed));
        add_event_listener(METHOD_LISTENER(Events::Player::SCORE, "room", room_state::score_changed));

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
        pl = create_entity("player");

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
        pl.add_component<native_script>({}).bind<player_controller>(data.player_health, data.score);


        // UI
        auto inventory = create_entity("inventory_manager");
        inventory.add_component<native_script>({}).bind<inventory_renderer>();

        auto hb = create_entity("healtbar");
        hb.add_component<transform>({{1, 2}, 1});
        hb.add_component<ui>({""});
        hb.add_component<native_script>({}).bind<healtbar_controller>();

        auto sb = create_entity("scorebar");
        sb.add_component<transform>({{1, 3}, 1});
        sb.add_component<ui>({""});
        sb.add_component<native_script>({}).bind<score_controller>();

        auto h_text = create_entity("h_text");
        h_text.add_component<transform>({0, 1});
        h_text.add_component<ui>({"Press 'h' to open the help menu"});

        auto inv = create_entity("inv");
        inv.add_component<transform>({{1, 5}});
        inv.add_component<ui>({"Inventory"});

        auto minimap = create_entity("minimap");
        minimap.add_component<transform>({{COLS - 14 , 1}});
        minimap.add_component<ui>({"Minimap", 0, true, true});

        auto level = create_entity("inv");
        level.add_component<transform>({{COLS / 2, 1}});
        level.add_component<ui>({"World " + std::to_string(data.world_gen->get_current_world_index() + 1), 0, true, true});

        brown::add_sprite({"a"}, "bot3");
        brown::add_sprite({"a"}, "bot2");
        auto pot = create_entity("potion1");
        pot.add_component<transform>({{40, 16}});
        pot.add_component<sprite>({{1, 1}, "bot2"});
        pot.add_component<native_script>({}).bind<potion>(4);

        auto pot1 = create_entity("potion2");
        pot1.add_component<transform>({{50, 16}});
        pot1.add_component<sprite>({{1, 1}, "bot2"});
        pot1.add_component<native_script>({}).bind<potion>(4);
/*
        auto bot3 = create_entity();
        bot3.add_component<transform>({offset + vec2{rand() % (map_size.x * TILE_SIZE), rand() % (map_size.y * TILE_SIZE)}, 1});
        brown::add_sprite({"a"}, "bot3");
        bot3.add_component<sprite>({{1, 1}, "bot3"});
        bot3.add_component<native_script>({}).bind<ranged_enemy>();
        bot3.add_component<ui>({"", 0, true, true});
*/
        initialized = true;
    }

    void cleanup() {}
    void pause()
    {
        m_pause = true;
        player_controller *pl_controller = dynamic_cast<player_controller *>(pl.get_component<native_script>().instance);
    pl_controller->m_inventory = *data.player_inventory;
        pl_controller->set_health(data.player_health);
        pl_controller->set_score(data.score);
    }
    void resume()
    {
        m_pause = false;
        player_controller *pl_controller = dynamic_cast<player_controller *>(pl.get_component<native_script>().instance);

        pl_controller->m_inventory = *data.player_inventory;

        pl_controller->set_health(data.player_health);
        pl_controller->set_score(data.score);
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

    void draw_minimap(vec2 pos, WINDOW* win);
    
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

            draw_minimap({COLS - 24, 3}, win);
        }
    }

    int last_entered = 0;

protected:
    std::shared_ptr<brown::animation_system> animation_system;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
    std::shared_ptr<brown::UI_system> UI_system;

    std::shared_ptr<tile_system> tiles_system;

    vec2 offset = 0;
    bool m_pause = false;

    tileset *ts = nullptr;

    int frame_passed = 0;

    brown::entity pl;

    room_data data;
};