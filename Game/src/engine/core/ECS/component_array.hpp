#pragma once

#include "../types.hpp"
#include <array>
#include "debug/debugger.hpp"
#include <unordered_map>

namespace brown
{
    class Vcomponent_array
    {
    public:
        virtual ~Vcomponent_array() = default;
        virtual void entity_destroyed(entity_id entity) = 0;
    };

    template <typename T>
    class component_array : public Vcomponent_array
    {
    public:
        void insert_data(entity_id entity, T component)
        {
            size_t new_index = m_size;
            m_entity_to_index[entity] = new_index;
            m_index_to_entity[new_index] = entity;
            m_component_array[new_index] = std::forward<T>(component);
            ++m_size;
        }

        void remove_data(entity_id entity)
        {

            // Copy element at end into deleted element's place to maintain density
            size_t rem = m_entity_to_index[entity];
            size_t last = m_size - 1;
            m_component_array[rem] = m_component_array[last];

            // Update map to point to moved spot
            std::uint32_t e_last = m_index_to_entity[last];
            m_entity_to_index[e_last] = rem;
            m_index_to_entity[rem] = e_last;

            m_entity_to_index.erase(entity);
            m_index_to_entity.erase(last);

            --m_size;
        }

        T &get_data(entity_id entity)
        {
            ASSERT(m_entity_to_index.find(entity) != m_entity_to_index.end(), "Entity doesn't have the component requested!");
            return m_component_array[m_entity_to_index[entity]];
        }

        void entity_destroyed(entity_id entity) override
        {
            if (m_entity_to_index.find(entity) != m_entity_to_index.end())
            {
                remove_data(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> m_component_array{};
        std::unordered_map<entity_id, size_t> m_entity_to_index{};
        std::unordered_map<size_t, entity_id> m_index_to_entity{};
        size_t m_size;
    };
}