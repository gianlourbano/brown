#include "physics_system.hpp"
#include "../components/force.hpp"
#include "../components/transform.hpp"
#include "../components/force.hpp"

void brown::physics_system::init() {}

void brown::physics_system::update(brown::brain *br)
{
    for (auto const &entity : m_entities)
    {
        auto &rigid = br->get_component<rigid_body>(entity);
        auto &tr = br->get_component<transform>(entity);
        auto &f = br->get_component<force>(entity);

        tr.position += rigid.velocity;
        rigid.velocity += f.f;
    }
}

void brown::physics_system::handle_events(brown::brain *br)
{
    for (auto const &entity : m_entities)
    {
        auto &rigid = br->get_component<rigid_body>(entity);
        auto &f = br->get_component<force>(entity);
        if (rigid.velocity.x == 0)
        f.f = {0, 0};
    }
}