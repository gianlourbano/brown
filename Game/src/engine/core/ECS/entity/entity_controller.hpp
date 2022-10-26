#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "entity.hpp"
#include "core/brain.hpp"
#include "core/ECS/components/native_script.hpp"

namespace brown
{
    class entity_controller
    {
    public:
        entity_controller(){};
        void init(brown::brain *br) { m_brain = br; }

        brown::entity find(entity_id id)
        {
            for (auto &e : m_entities)
            {
                if (e.m_entity_id == id)
                    return e;
            }
            ERROR("Entity not found!");
            return {};
        }

        brown::entity find(std::string name)
        {
            for (auto &e : m_entities)
            {
                if (e.name == name)
                    return e;
            }
            ERROR("Entity not found!");
            return {};
        }

        void delete_entity(brown::entity e)
        {
            to_be_deleted.push_back(e);
        }

        void LOG_ENTITIES()
        {
            for (auto &e : m_entities)
            {
                LOG(e.name + " :" + std::to_string(e.m_entity_id));
            }
        }

        void empty_to_be_deleted()
        {
            for (auto &e : to_be_deleted)
            {
                auto &script = m_brain->get_component<native_script>(e.get_id());

                script.instance->on_destroy();

                script.destroy_script(&script);

                m_brain->destroy_entity(e.m_entity_id);
                m_entities.erase(std::find(m_entities.begin(), m_entities.end(), e));
            }
            to_be_deleted.clear();
        }

    private:
        friend class state;

        std::vector<brown::entity> m_entities;
        std::vector<brown::entity> to_be_deleted{};
        brown::brain *m_brain = nullptr;
    };
}