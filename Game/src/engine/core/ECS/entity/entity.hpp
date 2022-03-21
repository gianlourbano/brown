#pragma once
#include "core/types.hpp"
#include "core/brain.hpp"
#include <typeinfo>

namespace brown
{
    enum Z_INDEX
    {
        Z_0,
        Z_1,
        Z_2
    };

    class entity
    {
    public:
        entity(){};
        entity(std::string name, entity_id id, brain *br, Z_INDEX z_index) :name(name), m_entity_id(id), m_brain(br), z_index(z_index){};
        entity(std::string name, entity_id id, brain *br) : name(name), m_entity_id(id), m_brain(br), z_index(brown::Z_1){};
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
        Z_INDEX z_index = Z_1;
    protected:
        friend class scriptable_entity;
    };
}