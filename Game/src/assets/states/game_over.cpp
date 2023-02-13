#include "game_over.hpp"

void game_over::init(brown::engine *game)
{
    m_game = game;

    set_win(brown::graphics::create_newwin(LINES, COLS, 0, 0));
    brown::graphics::start_curses_flags(win);
    game->set_current_screen(win);

    brain.init();

    m_ui_system = brown::UI_system::register_system(&brain);

    m_controller.init(&brain);

    auto title = create_entity("title");
    title.add_component<transform>({{COLS / 2, LINES / 2 - 1}});
    title.add_component<ui>({"Game Over", 0, true, true});

    auto score = create_entity("score");
    score.add_component<transform>({{COLS / 2, LINES / 2 + 1}});
    score.add_component<ui>({"Score: " + std::to_string(m_final_score), 0, true, true});

    auto key = create_entity("key");
    key.add_component<transform>({{COLS / 2, LINES / 2 + 3}});
    key.add_component<ui>({"Press any key to continue...", 0, true, true});
}

void game_over::handle_events(brown::engine *game)
{
    brown::get_keyboard_input(win);
    if (brown::KEY_PRESSED != ERR)
    {
        game->quit();
    }
}

void game_over::update(brown::engine *game)
{
}

void game_over::draw(brown::engine *game)
{
    werase(win);
    wbkgdset(win, COLOR_PAIR(9));

    m_ui_system->draw(win, &brain);
}