#pragma once

namespace brown::colors {
    void start_colors();

    void init_color_from_rgb(short id, short r, short g, short b);

    void make_pair(short pair_id, short color_A_id, short color_B_id);
}