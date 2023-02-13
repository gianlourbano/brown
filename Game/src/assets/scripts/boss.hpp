#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/projectile.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/projectile_boss.hpp"
#include "assets/scripts/ranged_enemy.hpp"

class boss_enemy : public scriptable_enemy
{
public:
    boss_enemy(enemy_stats stats) : scriptable_enemy(stats) {}

    bool check_collision(int dir);
    void on_create();
    void on_update();
    void on_destroy();

private:
    int m_health;
    ui *m_healthbar;
    animation proj_anim;
    brown::Timer t;
    brown::Timer damage_t;
    brown::Timer t_attack;
    player_controller *m_player;
    int m_proj_lifespan = 0;
    bool can_shoot = true;
    int exp = 150;
};
