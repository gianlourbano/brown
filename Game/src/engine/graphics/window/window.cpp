#include "window.hpp"

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
                    {
                        if (c == '#')
                            id = 5;
                        else if (c == '%')
                            id = 4;
                        else if (c == ' ' || c == '.')
                            id = 6;
                        else if (c == 'x')
                            id = 3;
                        else if (c == 'a')
                            id = 10;
                        else if( c == '6')
                            id = 11;
                    }
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