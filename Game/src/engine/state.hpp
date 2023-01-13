#include <ncurses.h>
#include "core/brain.hpp"
#include "core/ECS/entity/entity.hpp"
#include "core/ECS/entity/entity_controller.hpp"

namespace brown
{

    class engine;

    /**
     * @brief The state class
     *
     * This is the template for all the states of the game.
     * All of the methods are pure virtual and are to be implemented by the child class.
     *
     */
    class state
    {
    public:
        virtual void init(engine *game) = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        /**
         * @brief Handles the game logic.
         *
         * @param game the pointer to the engine instance.
         */
        virtual void handle_events(engine *game) = 0;

        /**
         * @brief Updates the game logic.
         *
         * @param game the pointer to the engine instance.
         */
        virtual void update(engine *game) = 0;

        /**
         * @brief Draws the drawables to the screen.
         *
         * @param game the pointer to the engine instance.
         */
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

        std::vector<entity> get_entities() { return m_controller.m_entities; }

        inline void add_event_listener(event_id id, std::string name, const std::function<void(brown::event &)> listener) { brain.add_event_listener(id, name, listener); }
        inline void remove_event_listener(event_id id, std::string name) { brain.remove_event_listener(id, name); }
        inline void send_event(event_id id) { brain.send_event(id); }
        inline void send_event(event e) { brain.send_event(e); }

        inline void game_over() { terminate = true; }

    protected:
        state(){};
        bool terminate = false;
        WINDOW *win = nullptr;
        brown::engine *m_game = nullptr;
        brown::brain brain;
        unsigned int free_entities = 0;
        brown::entity_controller m_controller;

    private:
        friend class scripts_system;
    };

}