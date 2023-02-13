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

#include "assets/scripts/player_controller.hpp"

#include "inventory_state.hpp"

#define TILES 30

struct room_data
{
    int id = -1;

    player_data m_player_data;
    world_generator *world_gen = nullptr;

    // room data
    int direction = 0;

    room_data() {}
    room_data(int id, player_data data, world_generator *world_gen, int direction)
    {
        this->id = id;
        this->m_player_data = data;
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

    void data_changed(brown::event &e)
    {
        data.m_player_data = e.get_param<player_data>(Events::Player::Data::DATA);
    }
    room_data *get_data() { return &data; }

    void key_picked_up(brown::event &e)
    {
        data.world_gen->get_current_generator()->key_picked_up();
    }

    void enemy_killed(brown::event &e)
    {
        m_enemies_alive--;

        ui *score = &find_entity("counter").get_component<ui>();
        score->text = std::to_string(m_enemies_alive) + "/" + std::to_string(m_enemies);
    }

    void generate_doors(tilemap &tm);
    vec2 get_valid_position();

    void init(brown::engine *game)
    {
        m_game = game;

        set_win(brown::graphics::create_newwin(LINES, COLS, 0, 0));
        brown::graphics::start_curses_flags(win);
        game->set_current_screen(win);

        brain.init();

        add_event_listener(METHOD_LISTENER(Events::Player::DATA, "room", room_state::data_changed));
        add_event_listener(METHOD_LISTENER(Events::Room::Key_picked_up, "room", room_state::key_picked_up));
        add_event_listener(METHOD_LISTENER(Events::Room::Enemy_killed, "room", room_state::enemy_killed));

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
        int row, col;
        getmaxyx(win, row, col);

        offset.x = (col - map_size.x * TILE_SIZE) / 2;
        offset.y = (row - map_size.y * TILE_SIZE) / 2;
        if (offset.y < 7)
            offset.y = 7;
        map.add_component<transform>({offset, 0});
        tilemap &tm = map.add_component<tilemap>({ts, map_size.x, map_size.y});
        tm.load_from_file("tilemap_" + std::to_string(rand() % 13 + 1));

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
        pl.add_component<native_script>({}).bind<player_controller>(data.m_player_data);

        // UI
        auto inventory = create_entity("inventory_manager");
        inventory.add_component<native_script>({}).bind<inventory_renderer>();
        send_event(Events::Player::Inventory::ADD);

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
        minimap.add_component<transform>({{COLS - 14, 1}});
        minimap.add_component<ui>({"Minimap", 0, true, true});

        auto level = create_entity("world");
        level.add_component<transform>({{COLS / 2, 1}});
        level.add_component<ui>({"World " + std::to_string(data.world_gen->get_current_world_index() + 1), 0, true, true});

        auto counter = create_entity("counter");
        counter.add_component<transform>({{COLS / 2, 2}});
        counter.add_component<ui>({" ", 0, true, true});

        brown::add_sprite({"a"}, "bot3");
        brown::add_sprite({"o"}, "bot2");

        int num_potions = random_int(1, 2) + log(data.world_gen->get_current_world_index() + 1);
        for (int i = 0; i < num_potions; i++)
        {
            auto pot = create_entity("potion" + std::to_string(i));
            pot.add_component<transform>({get_valid_position()});
            pot.add_component<sprite>({{1, 1}, "bot2"});
            pot.add_component<native_script>({}).bind<potion>(random_int(5, 10) + log(data.world_gen->get_current_world_index() + 1));
        }

        if (rand() % 10 == 0)
        {
            auto charm = create_entity("charm");
            charm.add_component<transform>({get_valid_position()});
            charm.add_component<sprite>({{1, 1}, "bot3"});
            charm.add_component<native_script>({}).bind<vitality_charm>();
        }

        m_enemies_alive = random_int(2, 4) + log(data.world_gen->get_current_world_index() + 1);
        m_enemies = m_enemies_alive;
        for (int i = 0; i < m_enemies_alive; i++)
        {
            auto bot = create_entity("enemy" + std::to_string(i));
            bot.add_component<transform>({get_valid_position()});
            bot.add_component<sprite>({{1, 1}, "bot2"});
            bot.add_component<native_script>({}).bind<ranged_enemy>(enemy_stats());
            bot.add_component<ui>({"", 0, true, true});
        }

        if (data.world_gen->is_key_room(data.id))
        {
            auto key = create_entity("key");
            key.add_component<transform>({get_valid_position()});
            key.add_component<sprite>({{1, 1}, "bot3"});
            key.add_component<native_script>({}).bind<boss_key>();
        }

        initialized = true;
    }

    void cleanup() {}
    void pause()
    {
        m_pause = true;
        player_controller *pl_controller = dynamic_cast<player_controller *>(pl.get_component<native_script>().instance);
        pl_controller->update_data(data.m_player_data);
    }
    void resume()
    {
        m_pause = false;
        player_controller *pl_controller = dynamic_cast<player_controller *>(pl.get_component<native_script>().instance);

        pl_controller->update_data(data.m_player_data);
        send_event(Events::Player::Inventory::ADD);
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
                case 'i':
                    game->push_state(new inventory_state(data.m_player_data.player_inventory)); // m_controller.LOG_ENTITIES();))
                    break;
                case 'c':
                    game->pop_state();
                    break;
                case 'l':
                    game->quit();
                    break;
                case 'p':
                    m_pause = true;
                    break;
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

    void draw_minimap(vec2 pos, WINDOW *win);

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

    bool is_room_cleared() { return m_enemies_alive == 0; }

protected:
    std::shared_ptr<brown::animation_system> animation_system;
    std::shared_ptr<brown::render_system> render_system;
    std::shared_ptr<brown::scripts_system> scripts_system;
    std::shared_ptr<brown::UI_system> UI_system;

    std::shared_ptr<tile_system> tiles_system;

    vec2 offset = 0;
    vec2 map_size = {17, 6};
    bool m_pause = false;

    tileset *ts = nullptr;

    int frame_passed = 0;

    brown::entity pl;

    int m_enemies_alive = 0;
    int m_enemies = 0;

    room_data data;
};