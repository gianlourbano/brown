#include "inventory_state.hpp"

void inventory_state::init(brown::engine *game)
{
    m_game = game;

    set_win(brown::graphics::create_newwin(10, 2, 7, 20));
    brown::graphics::start_curses_flags(win);

    brain.init();

    m_UI_system = brown::UI_system::register_system(&brain);

    m_controller.init(&brain);

    arrow = create_entity("arrow");
    arrow.add_component<transform>({0});
    arrow.add_component<ui>({"<-", 0, true, true});

    m_current_item;
}

void inventory_state::cleanup(){};
void inventory_state::pause(){};
void inventory_state::resume(){};

void inventory_state::handle_events(brown::engine *game)
{
    brown::get_keyboard_input(win);

    if (brown::KEY_PRESSED != ERR)
    {
        switch (brown::KEY_PRESSED)
        {
        case KEY_UP:
        {
            if (m_current_item_index > 0)
            {
                m_current_item_index--;
                arrow.get_component<transform>().position.y--;
            }
            break;
        }
        case KEY_DOWN:
        {
            if (m_current_item_index < m_inventory.size())
            {
                m_current_item_index++;
                arrow.get_component<transform>().position.y++;
            }
            break;
        }
        case 'e':
        {
            if (m_current_item_index >= m_inventory.size() || m_current_item_index < 0)
                break;
            m_current_item = m_inventory[m_current_item_index];
            if (m_current_item == nullptr)
                break;
            consumable *consumable_item = dynamic_cast<consumable *>(m_current_item);
            if (consumable_item != nullptr)
            {
                consumable_item->on_use();
                game->pop_state();
            }

            break;
        }
        case 'r':
        {
            m_current_item = m_inventory[m_current_item_index];
            
            artifact *artifact_item = dynamic_cast<artifact *>(m_current_item);
            if (artifact_item != nullptr)
            {
                artifact_item->on_remove();
            }
            if (m_current_item == nullptr)
                break;
            m_inventory_ptr->remove_item(m_current_item->m_name);
            game->pop_state();
            break;
        }
        case 'i':
        {
            game->pop_state();
            break;
        }
        }
    }
};
void inventory_state::update(brown::engine *game){};
void inventory_state::draw(brown::engine *game)
{
    werase(win);
    wbkgdset(win, COLOR_PAIR(8));

    m_UI_system->draw(win, &brain);

    // brown::graphics::mvwprintwcolors(win, m_current_item_pos.y, m_current_item_pos.x,30, "<-");
};