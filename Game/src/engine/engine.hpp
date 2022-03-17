#pragma once

#include "core/types.hpp"
#include <ncurses.h>
#include <vector>
#include <unordered_map>
#include "core/brain.hpp"
#include "core/ECS/entity/entity.hpp"
#include "core/ECS/entity/entity_controller.hpp"

namespace brown
{
    class engine;
    /*
        state class for managing scenes basically.
        the user needs to implement all the virtual functions
        whenever he creates custom states.
    */

    class state
    {
    public:
        virtual void init(engine *game) = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void handle_events(engine *game) = 0;
        virtual void update(engine *game) = 0;
        virtual void draw(engine *game) = 0;

        void change_state(engine *game, state *state);

        WINDOW *get_win() { return win; }
        void set_win(WINDOW *win) { this->win = win; }

        friend class entity;

        entity create_entity(std::string s);
        entity create_entity();
        entity find_entity(std::string s);
        entity_id find_entity_id(std::string s);
        void delete_entity(std::string s);

        // template <typename T>
        // void remove_component(std::string s)
        // {
        //     brain.remove_component<T>(m_entities[s]);
        // }

    protected:
        state(){};
        WINDOW *win;
        brown::brain brain;
        unsigned int free_entities = 0;
        brown::entity_controller m_controller;
    };

    class engine
    {
    public:
        void init(int width, int height);
        void cleanup();

        void change_state(state *state);
        void push_state(state *state);
        void pop_state();

        void handle_events();
        void update();
        void draw();

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