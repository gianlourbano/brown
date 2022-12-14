#pragma once
#include "entity.hpp"
#include "engine/math/vec2.hpp"
#include "engine/core/ECS/components/transform.hpp"

#define SCRIPT(name) class name : public brown::scriptable_entity {
#define END_SCRIPT };

namespace brown
{
    class state;

    class scriptable_entity
    {
    public:
        scriptable_entity() {}
        virtual ~scriptable_entity() {}

        template <typename T>
        T &get_component() { return m_entity.get_component<T>(); }

        template <typename T>
        T &add_component(T component) { return m_entity.add_component<T>(component); }

        template <typename T>
        void delete_component() { m_entity.remove_component<T>(); }

        bool is_player_in_range(double range);

        void delete_self();

    public:
        virtual void on_create() {}
        virtual void on_destroy() {}
        virtual void on_update() {}
    protected:
        entity m_entity;
        state *m_state;

    private:
        friend class scene;
        friend class entity;
        friend class scripts_system;
        friend class entity_controller;
    };
}