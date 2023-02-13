#pragma once
#include "brown.hpp"

class projectile_boss : public brown::scriptable_entity
{
public:
    bool check_collision(int dir);
    void on_create();
    void on_update();
    void on_destroy();

    projectile_boss(entity_id creator) : m_creator_id(creator) {}

private:
    bool has_finished = false;
    vec2 force;
    bool timer_started = false;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
    brown::Timer t_end;

    entity_id m_creator_id;
};