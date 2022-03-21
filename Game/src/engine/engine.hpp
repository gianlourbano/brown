#pragma once

#include "core/types.hpp"
#include <ncurses.h>
#include <vector>
#include "state.hpp"

namespace brown
{

    class engine
    {
    public:
        void init(int width, int height);
        void cleanup();

        void change_state(state *state);
        void push_state(state *state);
        void pop_state();

        void update();
        void handle_events();
        void draw();

        void run();
        bool running() { return m_running; }
        void quit();

        WINDOW *get_std_screen() { return stdscreen; }
        WINDOW *get_current_screen() { return current_screen; }
        void set_current_screen(WINDOW *win) { current_screen = win; }

    private:
        // standard screen output
        WINDOW *stdscreen;
        WINDOW *current_screen;

        // the stack of states
    public:
        std::vector<state *> states;
        bool m_running;
    };
}