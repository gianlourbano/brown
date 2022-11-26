#pragma once
#include "core/types.hpp"
#include "core/brain.hpp"
#include <typeinfo>

namespace brown
{

    class entity
    {
    public:
        entity(){};
        entity(std::string name, entity_id id, brain *br) :name(name), m_entity_id(id), m_brain(br){};
        entity(const entity &) = default;

        template <typename T>
        T &add_component(T component)
        {
            m_brain->add_component<T>(m_entity_id, std::forward<T>(component));
            return m_brain->get_component<T>(m_entity_id);
        }

        template <typename T>
        void remove_component() {}

        entity_id get_id() { return m_entity_id; }
        signature get_signature() { return m_brain->get_signature(m_entity_id); }

        friend class state;
        friend class entity_controller;

        void delete_entity() {  };

        template <typename T>
        T &get_component() { return m_brain->get_component<T>(m_entity_id); }

        bool operator==(const entity& e) {
            return this->m_entity_id == e.m_entity_id;
        }

        std::string name;
    private:
        entity_id m_entity_id;
        brain *m_brain = nullptr;
    protected:
        friend class scriptable_entity;
    };
}