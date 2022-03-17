#include <ncurses.h>
#include "color.hpp"
#include "../../debug/debugger.hpp"

namespace brown::colors
{
    //starts color mode on the terminal, if supported.
    void start_colors() {
        if(has_colors() == FALSE) {
            ERROR("Colors not supported!");
            endwin();
        }
        start_color();
    }

    //inits a color from a rgb value; the id can be in the range of 8:255
    void init_color_from_rgb(short id, short r, short g, short b) {
        const int p = 1000 / 255;
        init_color(id, r * p, g * p, b * p);
    }

    /*inits a pair from two colors: 
    the first is the color of the foreground, the second is the background*/
    void make_pair(short pair_id, short color_A_id, short color_B_id) {
        init_pair(pair_id, color_A_id, color_B_id);
    }
}