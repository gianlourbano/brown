#pragma once
#include <ncurses.h>

namespace brown
{
    extern size_t KEY_PRESSED;

    void get_keyboard_input(WINDOW *win);
}
