#include "engine/brown.hpp"
#include "assets/states/state_1.hpp"

int frame_passed = 0;
int FPS = 60;

brown::state_1 brown::state_1::m_state_1;

class game : public brown::engine
{
public:
    void init(int width, int height)
    {
        brown::engine::init(width, height);
        brown::colors::init_color_from_rgb(9, 43, 43, 43);
        brown::colors::init_color_from_rgb(10, 66, 62, 63);
        brown::colors::init_color_from_rgb(11, 23, 16, 16);

        brown::colors::init_color_from_rgb(12, 255, 229, 5);
        brown::colors::init_color_from_rgb(13, 255, 251, 5);
        brown::colors::init_color_from_rgb(14, 60, 217, 19);
        brown::colors::init_color_from_rgb(15, 222, 184, 135);
        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_BLUE, COLOR_BLUE);
        init_pair(2, COLOR_CYAN, COLOR_CYAN);
        init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(4, 11, 11);
        init_pair(5, 9, 9);
        init_pair(6, 10, 10);
        init_pair(7, 12, 12);
        init_pair(8, 13, 13);
        init_pair(9, COLOR_WHITE, 10);
        init_pair(10, 14, 14);
        init_pair(11, 15, 15);
    }
};

int main()
{
    game engine;

    engine.init(640, 480);

    engine.change_state(brown::state_1::instance());

    while (engine.running())
    {
        if (usleep(1000000 / FPS) == EINTR)
            break;

        engine.handle_events();
        engine.update();
        engine.draw();
    }

    endwin();

    return 0;
}