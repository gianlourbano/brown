#include "input.hpp"

namespace brown
{
    size_t KEY_PRESSED;

    void get_keyboard_input(WINDOW *win)
    {
        KEY_PRESSED = wgetch(win);
    }
}