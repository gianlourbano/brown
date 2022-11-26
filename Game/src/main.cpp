#include "engine/brown.hpp"
#include "assets/states/menu_state.hpp"

int FPS = 60;

menu_state menu_state::m_menu_state;

class game : public brown::engine
{
public:
    void init(int width, int height)
    {
        engine::init(width, height);
        brown::colors::start_colors();
        brown::colors::init_palette_from_file("palette");
        brown::colors::init_color_map_from_file("color");
    }
};

int main()
{
    game engine;

    engine.init(640, 480);

    engine.change_state(menu_state::instance());

    engine.run();

    endwin();

    return 0; 
}