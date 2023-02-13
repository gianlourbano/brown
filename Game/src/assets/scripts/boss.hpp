#pragma once
#include "scriptable_enemy.hpp"
#include "types.hpp"
#include "assets/scripts/projectile_boss.hpp"

class boss_enemy : public scriptable_enemy
{
public:
    boss_enemy(enemy_stats stats) : scriptable_enemy(stats) {}

    void on_create();
    void on_update();
    void on_destroy();

private:
    brown::Timer t_attack;

    animation proj_anim = {
            "animated1",
            2,
            5,
            5,
            false,
            true};;
    int m_proj_lifespan = 0;
    bool can_shoot = true;
};
