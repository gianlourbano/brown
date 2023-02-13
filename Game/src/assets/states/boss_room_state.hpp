#include "room_state.hpp"

class boss_room_state : public room_state
{
    public:
        boss_room_state() = delete;
        boss_room_state(room_data data) : room_state(data) {}

        void init(brown::engine *game) {
            room_state::init(game);

            auto bs = create_entity("bs");
            bs.add_component<transform>({{COLS / 2, LINES / 2}, 1});
            bs.add_component<ui>({""});
            bs.add_component<sprite>({{0,0}, "sprite_boss"});
            bs.add_component<native_script>({}).bind<boss_enemy>(enemy_stats());
        }

        void handle_events(brown::engine *game) {
            if (!m_pause) {
                if(world_cleared ){//&& data.world_gen->is_fully_explored()) {
                    advance(game);
                }

                brown::get_keyboard_input(win);
                if (brown::KEY_PRESSED != ERR) {
                    switch (brown::KEY_PRESSED) {
                        case 'm':
                            world_cleared = true;
                            break;
                    }
                }
            }
        }

        void advance(brown::engine *game) {
            data.m_player_data.player_inventory->remove_item("Boss room key");
            data.world_gen->generate_new_world(data.m_player_data);
            game->push_state(data.world_gen->get_current_world()[45]);
        }

    private:
        bool world_cleared = false;
};