#include "state.hpp"

namespace brown
{
    entity state::create_entity(std::string name)
    {
        entity_id e = brain.create_entity();
        entity e_ = entity(name, e, &(this->brain));
        m_controller.m_entities.push_back(e_);
        return e_;
    }

    entity state::create_entity()
    {
        entity_id e = brain.create_entity();
        entity e_ = entity("entity_" + std::to_string(free_entities++), e, &(this->brain));
        m_controller.m_entities.push_back(e_);
        return e_;
    }

    entity state::find_entity(std::string name)
    {
        return m_controller.find(name);
    }

    void state::delete_entity(entity_id id)
    {
        m_controller.delete_entity(m_controller.find(id));
    }

    entity_id state::find_entity_id(std::string s)
    {
        return m_controller.find(s).m_entity_id;
    }

}