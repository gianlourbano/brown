#pragma once
#include <ncurses.h>

namespace brown
{
    static size_t KEY_PRESSED;

    void get_keyboard_input(WINDOW *win)
    {
        KEY_PRESSED = wgetch(win);
    }


}