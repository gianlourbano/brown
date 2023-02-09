#pragma once
#include "../types.hpp"
#include "../../debug/debugger.hpp"
#include "engine/std/array.hpp"
#include "engine/std/queue.hpp"

namespace brown
{
    class entity_manager
    {
    public:
        entity_manager()
        {
            for (entity_id entity = 0; entity < MAX_ENTITIES; ++entity)
                m_avaliable_entities.push(entity);
        }

        entity_id create_entity()
        {
            entity_id id = m_avaliable_entities.front();
            m_avaliable_entities.pop();
            ++m_entity_count;
            return id;
        }

        void destroy_entity(entity_id entity)
        {
            m_signatures[entity].reset();
            m_avaliable_entities.push(entity);
            --m_entity_count;
        }

        void set_signature(entity_id entity, signature signature)
        {

            m_signatures[entity] = signature;
        }

        signature get_signature(entity_id entity)
        {
            return m_signatures[entity];
        }

        private:
            dt::queue<entity_id> m_avaliable_entities{};
            dt::array<signature, MAX_ENTITIES> m_signatures{};
            entity_id m_entity_count;
    };
}