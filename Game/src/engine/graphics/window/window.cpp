#include "window.hpp"
#include <unordered_map>

extern std::unordered_map<char, int> char_map;

namespace brown::graphics
{
    WINDOW *create_newwin(int height, int width, int starty, int startx)
    {
        WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0, 0); /* 0, 0 gives default characters
                               * for the vertical and horizontal
                               * lines			*/
        wrefresh(local_win);  /* Show that box 		*/

        return local_win;
    }

    void destroy_win(WINDOW *local_win)
    {
        wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(local_win);
        delwin(local_win);
    }

    void mvwprintwcolors(WINDOW *win, int y, int x, int pair, const char *s, ...)
    {
        va_list ptr;
        wattron(win, COLOR_PAIR(pair));
        mvwprintw(win, y, x, s, ptr);
        wattroff(win, COLOR_PAIR(pair));
    }

    void mvwaddchcolors(WINDOW *win, int y, int x, int pair, char c)
    {
        wattron(win, COLOR_PAIR(pair));
        mvwaddch(win, y, x, c);
        wattroff(win, COLOR_PAIR(pair));
    }

    void mvwprintvcolors(WINDOW *win, int y, int x, bool color, std::vector<std::string> spr)
    {
        int j;
        for (int i = 0; i < spr.size(); i++)
        {
            j = 0;
            for (auto c : spr[i])
            {
                if (c != ',')
                {
                    int id = 0;
                    if (color)
                        id = char_map[c];
                    
                    mvwaddchcolors(win, i + 1 + y, j + 1 + x, id, c != '.' ? c : ' ');
                }
                j++;
            }
        }
    }

    void start_curses_flags(WINDOW *win)
    {
        keypad(win, TRUE);
        cbreak();
        nodelay(win, TRUE);
        wrefresh(win);
    }
}