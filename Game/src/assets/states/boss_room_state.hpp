#include "room_state.hpp"

class boss_room_state : public room_state
{
public:
    boss_room_state() = delete;
    boss_room_state(room_data data) : room_state(data) {}

    void on_world_cleared(brown::event &e)
    {
        world_cleared = true;
        ui *u = get_entity("hooray").get_component<ui>();
        ui->is_visible = true;
    }

    void init(brown::engine *game)
    {
        room_state::init(game);

        auto hooray = create_entity("hooray");
        hooray.add_component<transform>({{COLS / 2, 4}});
        hooray.add_component<ui>({"You have cleared the dungeon! Press M to advance to the next world!", 0, false, true});

        add_event_listener(METHOD_LISTENER(Events::Room::World_cleared, "boss_room_state", boss_room_state::on_world_cleared));

        auto bs = create_entity("bs");
        bs.add_component<transform>({{COLS / 2, LINES / 2}, 1});
        bs.add_component<ui>({""});
        bs.add_component<sprite>({{0, 0}, "sprite_boss"});
        bs.add_component<native_script>({}).bind<boss_enemy>(enemy_stats());
    }

    void handle_events(brown::engine *game)
    {
        if (!m_pause)
        {
            if (world_cleared && data.world_gen->is_fully_explored())
            {
                advance(game);
            }

            brown::get_keyboard_input(win);
            if (brown::KEY_PRESSED != ERR)
            {
                switch (brown::KEY_PRESSED)
                {
                case 'm':
                    if (world_cleared && data.world_gen->is_fully_explored())
                    {
                        advance(game);
                    }
                    break;
                case 'i':
                    game->push_state(new inventory_state(data.m_player_data.player_inventory));
                    break;
                }
            }
        }
    }

    void advance(brown::engine *game)
    {
        data.m_player_data.player_inventory->remove_item("Boss room key");
        data.world_gen->generate_new_world(data.m_player_data);
        game->push_state(data.world_gen->get_current_world()[45]);
    }

private:
    bool world_cleared = false;
};