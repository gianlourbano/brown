#include <ncurses.h>
#include <fstream>
#include <unordered_map>
#include "color.hpp"
#include "../../debug/debugger.hpp"

std::string color_path = "./src/assets/colors/";
std::unordered_map<std::string, int> color_palette;
size_t CURR_ID = 8;
size_t CURR_PAIR_ID = 1;

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

    void init_palette_from_file(std::string palette) {
        std::ifstream palette_file(color_path + palette + ".color");

        std::string str;
        int r, g, b;

        while(palette_file >> str >> r >> g >> b) {
            init_color_from_rgb(CURR_ID, r, g, b);
            make_pair(CURR_PAIR_ID, CURR_ID, CURR_ID);
            color_palette.insert(std::make_pair(str, CURR_PAIR_ID));
            CURR_ID++; CURR_PAIR_ID++;
        }

    }
}