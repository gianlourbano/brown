#include "engine.hpp"
#include "core/color/color.hpp"
#include "core/ECS/entity/entity.hpp"
#include <unistd.h>

extern const int FPS;

namespace brown
{
    void engine::init(int width = 640, int height = 480)
    {
        // setlocale(LC_ALL, "");
        stdscreen = initscr();         /* Start curses mode 		*/
        brown::colors::start_colors(); // starts color mode -from colors.hpp
        noecho();                      // prevents user-inputted charters to be displayed on the stdscreen
        nodelay(stdscreen, true);      // makes getch non-blocking
        raw();                         // ncurses will report any keystrokes with getch immediately
        curs_set(0);                   // hide the cursor by default
        keypad(stdscreen, true);

        m_running = true;

        wrefresh(stdscreen);
    }

    void engine::quit()
    {
        this->m_running = false;
    }

    void engine::handle_events()
    {
        states.back()->handle_events(this);
    }

    void engine::update()
    {

        states.back()->update(this);
    }

    void engine::draw()
    {
        states.back()->draw(this);
    }

    void engine::change_state(state *state)
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        states.push_back(state);
        states.back()->init(this);
    }

    void engine::push_state(state *state)
    {
        if (!states.empty())
        {
            states.back()->pause();
        }

        states.push_back(state);
        states.back()->init(this);
    }

    void engine::pop_state()
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        if (!states.empty())
        {
            states.back()->resume();
        }
    }

    void change_state(engine *game, state *state) { game->change_state(state); }

    void engine::run() {
        while (this->running())
    {
        if (usleep(1000000 / FPS) == EINTR)
            break;

        this->handle_events();
        this->update();
        this->draw();
    }
    }

    entity state::create_entity(std::string name)
    {
        entity_id e = brain.create_entity();
        entity e_ = entity(name, e, &(this->brain));
        m_controller.m_entities.push_back(e_);
        return e_;
    }

    entity state::create_entity()
    {
        entity_id e = brain.create_entity();
        entity e_ = entity("entity_" + std::to_string(free_entities++),e, &(this->brain));
        m_controller.m_entities.push_back(e_);
        return e_;
    }

    entity state::find_entity(std::string name)
    {
        return m_controller.find(name);
    }

    void state::delete_entity(std::string name)
    {
        m_controller.delete_entity(m_controller.find(name));
    }

    entity_id state::find_entity_id(std::string s)
    {
        return m_controller.find(s).m_entity_id;
    }

}
