#pragma once
#include "entity.hpp"

namespace brown
{
    class state;

    class scriptable_entity
    {
    public:
        virtual ~scriptable_entity() {}

        template <typename T>
        T &get_component() { return m_entity.get_component<T>(); }

        void delete_self();

    protected:
        virtual void on_create() {}
        virtual void on_destroy() {}
        virtual void on_update() {}
        entity m_entity;
        state *m_state;

    private:
        friend class scene;
        friend class entity;
        friend class scripts_system;
        friend class entity_controller;
    };
}