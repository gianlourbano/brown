#include <ncurses.h>
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
        void delete_entity(entity_id id);

    protected:
        state(){};
        WINDOW *win;
        brown::brain brain;
        unsigned int free_entities = 0;
        brown::entity_controller m_controller;

    private:
        friend class scripts_system;
    };

}