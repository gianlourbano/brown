#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/player_controller.hpp"

struct enemy_stats
{
    int health = 50;
    int damage = 10;
    int defense = 5;

    int exp = 150;
};

class scriptable_enemy : public scriptable_AI
{

protected:
    enemy_stats m_stats;

    ui *m_healthbar;

    brown::Timer t;
    brown::Timer damage_t;
    brown::Timer t_move;

public:
    scriptable_enemy(enemy_stats stats): m_stats(stats) {}

    void on_hit(int) override;
    void die();
};