#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/projectile.hpp"
#include "assets/scripts/player_controller.hpp"

class ranged_enemy : public scriptable_enemy
{
public:
    ranged_enemy(enemy_stats stats) : scriptable_enemy(stats) {}
    
    void on_create();
    void on_update();
    void on_destroy();

private:
    animation proj_anim = {
            "animated1",
            2,
            3,
            5,
            false,
            true};;

    int m_proj_lifespan = 0;
    bool can_shoot = true;
};
