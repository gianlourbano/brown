#pragma once

#include "component_array.hpp"
#include "../types.hpp"
#include <any>
#include <memory>
#include <unordered_map>
#include "../../debug/debugger.hpp"

namespace brown
{

    class component_manager
    {
    public:
        template <typename T>
        void register_component()
        {
            const char *type_name = typeid(T).name();

            ASSERT(m_component_types.find(type_name) == m_component_types.end(), "Registering component type more than once.");

            m_component_types.insert({type_name, m_next_component_type});
            m_component_arrays.insert({type_name, std::make_shared<component_array<T>>()});

            ++m_next_component_type;
        };

        template <typename T>
        component_type get_component_type()
        {
            const char *type_name = typeid(T).name();

            ASSERT(m_component_types.find(type_name) != m_component_types.end(), "Component not registered before use.");

            return m_component_types[type_name];
        };

        template <typename T>
        void add_component(entity_id entity, T component)
        {
            get_component_array<T>()->insert_data(entity, component);
        }
        template <typename T>
        void remove_component(entity_id entity)
        {
            get_component_array<T>()->remove_data(entity);
        }
        template <typename T>
        T& get_component(entity_id entity)
        {
            return get_component_array<T>()->get_data(entity);
        }

        void entity_destroyed(entity_id entity)
        {
            for (auto const &pair : m_component_arrays)
            {
                auto const &component = pair.second;
                component->entity_destroyed(entity);
            }
        }

    private:
        std::unordered_map<const char *, component_type> m_component_types{};
        std::unordered_map<const char *, std::shared_ptr<Vcomponent_array>> m_component_arrays{};
        component_type m_next_component_type;

        template <typename T>
        std::shared_ptr<component_array<T>> get_component_array()
        {
            const char *type_name = typeid(T).name();

            return std::static_pointer_cast<component_array<T>>(m_component_arrays[type_name]);
        }
    };
}