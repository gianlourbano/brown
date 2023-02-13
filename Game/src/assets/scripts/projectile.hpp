#pragma once
#include "brown.hpp"
#include "scriptable_enemy.hpp"

static vec2 forces[4] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}};

class projectile : public brown::scriptable_entity
{
public:
    bool check_collision(int dir);
    void on_create();
    void on_update();
    void on_destroy();
    int get_lifetime();
    
    projectile(entity_id creator, int damage = 0) : m_creator_id(creator), damage(damage) {}

private:
    int lifetime;
    bool has_finished = false;
    vec2 force;
    int tot;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;

    int damage = 0;
    entity_id m_creator_id;
};