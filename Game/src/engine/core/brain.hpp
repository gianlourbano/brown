#pragma once
#include "event/event_manager.hpp"
#include "ECS/component_manager.hpp"
#include "ECS/entity_manager.hpp"
#include "ECS/system_manager.hpp"
#include "types.hpp"
#include <memory>
#include <unordered_map>
#include <string>

namespace brown
{
    class brain
    {
    public:
        void register_basic_components();

        void init()
        {
            m_component_manager = std::make_unique<component_manager>();
            m_entity_manager = std::make_unique<entity_manager>();
            m_system_manager = std::make_unique<system_manager>();
            m_event_manager = std::make_unique<event_manager>();

            register_basic_components();
        }

        // entity methods
        entity_id create_entity()
        {
            return m_entity_manager->create_entity();
        }

        void destroy_entity(entity_id entity)
        {
            m_entity_manager->destroy_entity(entity);
            m_component_manager->entity_destroyed(entity);
            m_system_manager->entity_destroyed(entity);
        }

        // components methods

        template <typename T>
        void register_component()
        {
            m_component_manager->register_component<T>();
        }

        template <typename T>
        void add_component(entity_id entity, T component)
        {
            m_component_manager->add_component<T>(entity, std::forward<T>(component));

            auto signature = m_entity_manager->get_signature(entity);
            signature.set(m_component_manager->get_component_type<T>(), true);
            m_entity_manager->set_signature(entity, signature);

            m_system_manager->entity_signature_changed(entity, signature);
        }

        template <typename T>
        void remove_component(entity_id entity)
        {
            m_component_manager->remove_component<T>(entity);

            auto signature = m_entity_manager->get_signature(entity);
            signature.set(m_component_manager->get_component_type<T>(), false);
            m_entity_manager->set_signature(entity, signature);

            m_system_manager->entity_signature_changed(entity, signature);
        }

        template <typename T>
        T &get_component(entity_id entity)
        {
            return m_component_manager->get_component<T>(entity);
        }

        template <typename T>
        component_type get_component_type()
        {
            return m_component_manager->get_component_type<T>();
        }

        // system methods
        template <typename T>
        std::shared_ptr<T> register_system()
        {
            return m_system_manager->register_system<T>();
        }

        template <typename T>
        void set_system_signature(signature signature)
        {
            m_system_manager->set_signature<T>(signature);
        }

        // event methods
        void add_event_listener(event_id id, std::function<void(event &)> const &listener)
        {
            m_event_manager->add_listener(id, listener);
        }

        void send_event(event &ev)
        {
            m_event_manager->send_event(ev);
        }

        void send_event(event_id id)
        {
            m_event_manager->send_event(id);
        }

    private:
        std::unique_ptr<component_manager> m_component_manager;
        std::unique_ptr<entity_manager> m_entity_manager;
        std::unique_ptr<system_manager> m_system_manager;
        std::unique_ptr<event_manager> m_event_manager;
    };
}