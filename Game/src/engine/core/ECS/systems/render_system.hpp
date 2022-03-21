#include "../system.hpp"
#include "../../brain.hpp"
#include "../components/sprite.hpp"
#include <ncurses.h>

namespace brown
{
    class render_system : public brown::system
    {
    public:
        static std::shared_ptr<render_system> register_system(brown::brain* br);

        void init();
        void draw(WINDOW *win, brain *br);
    };

    sprite_data load_sprite(std::string name);
    std::vector<sprite_data> load_animated_sprite(std::string name);
}