#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "entity.hpp"
#include "core/brain.hpp"

namespace brown
{
    class entity_controller
    {
    public:
        entity_controller() {};
        void init(brown::brain *br) { m_brain = br; }

        brown::entity find(std::string name)
        {
            for (auto &e : m_entities)
            {
                if (name == e.name)
                    return e;
            }
            ERROR("Entity not found!");
            return {};
        }

        void delete_entity(brown::entity e)
        {
            to_be_deleted.push_back(e);
        }

        void empty_to_be_deleted()
        {
            for (auto &e : to_be_deleted)
            {
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