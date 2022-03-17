#include "../system.hpp"
#include "../../brain.hpp"
#include "../components/sprite.hpp"
#include <ncurses.h>

namespace brown
{
    class render_system : public brown::system
    {
    public:
        void init();
        void draw(WINDOW *win, brain *br);
    };

    sprite_data load_sprite(std::string name);
    std::vector<sprite_data> load_animated_sprite(std::string name);
}