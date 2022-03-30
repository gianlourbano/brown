#include "engine/brown.hpp"
#include "assets/states/state_1.hpp"

int FPS = 60;

brown::state_1 brown::state_1::m_state_1;

class game : public brown::engine
{
public:
    void init(int width, int height)
    {
        brown::engine::init(width, height);
        brown::colors::init_palette_from_file("palette");
        brown::colors::init_color_map_from_file("color");
    }
};

int main()
{
    game engine;

    engine.init(640, 480);

    engine.change_state(brown::state_1::instance());

    engine.run();

    endwin();

    return 0;
}