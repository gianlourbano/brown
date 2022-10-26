#include "tileset.hpp"
#include <unordered_map>
#include <ncurses.h>

extern std::unordered_map<char, int> char_map;

void print_tile(WINDOW *win, tile t, vec2 pos)
{
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            brown::graphics::mvwaddchcolors(win, pos.y + 1 + j, pos.x + 1 + i, char_map[t.m_data.at(i, j)], t.m_data.at(i, j) == '.' ? ' ':t.m_data.at(i,j));
        }
    }
}