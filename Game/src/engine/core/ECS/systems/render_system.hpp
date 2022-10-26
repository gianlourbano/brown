#include "../system.hpp"
#include "../../brain.hpp"
#include "../components/sprite.hpp"
#include <ncurses.h>

using sprite_data = std::vector<std::string>;

namespace brown
{
    class render_system : public brown::system
    {
    public:
        static std::shared_ptr<render_system> register_system(brown::brain* br);

        void init();
        void draw(WINDOW *win, brain *br, Z_INDEX z = Z_INDEX::Z_2);
    };

    sprite_data load_sprite(std::string name);
    std::vector<sprite_data> load_animated_sprite(std::string name);
    void add_sprite(sprite_data sd, std::string name);
}