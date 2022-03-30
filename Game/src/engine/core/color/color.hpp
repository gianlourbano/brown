#pragma once
#include <string>

namespace brown::colors {
    void start_colors();

    void init_color_from_rgb(short id, short r, short g, short b);

    void make_pair(short pair_id, short color_A_id, short color_B_id);

    void init_palette_from_file(std::string palette);

    void init_color_map_from_file(std::string map);

    void add_custom_pair(short color_A_id, short color_B_id);
    void add_custom_color(short r, short g, short b);
}