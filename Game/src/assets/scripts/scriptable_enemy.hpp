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

    void on_hit(int);
    void die();

};

/*
class scriptable_enemy : public scriptable_AI
{
private:
    enemy_stats m_stats;

public:
    scriptable_enemy(enemy_stats stats) : m_stats(stats) {}

    bool check_collision(int dir);

    void on_hit();

    void on_create()
    {
        ts = &get_component<transform>();
        m_healthbar = &get_component<ui>();

        t.start();
        damage_t.start();
        t_move.start();
        m_health = 3;

        m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
    };
    void on_update()
    {
        auto pl = m_state->find_entity("player").get_component<transform>();
        player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        std::string hearts = " ";
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;
        m_healthbar->offset = vec2{-hearts.length() / 2, 0};
        if (is_player_in_range(10) && t_move.elapsed() >= 0.5 && !((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
        {
            t_move.start();
            int r = rand() % 2 + 1;

            if (r == 1)
            {
                if (ts->position.x != pl.position.x)
                {
                    if (ts->position.x > pl.position.x)
                    {
                        ts->direction = 4;
                        if (!check_collision(4))
                            ts->position.x--;
                    }
                    else
                    {
                        ts->direction = 2;
                        if (!check_collision(2))
                        {
                            LOG(mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT);
                            ts->position.x++;
                        }
                    }
                }
                else if (ts->position.y != pl.position.y)
                {
                    if (ts->position.y > pl.position.y)
                    {
                        ts->direction = 1;
                        if (!check_collision(1))
                            ts->position.y--;
                    }
                    else
                    {
                        ts->direction = 3;
                        if (!check_collision(3))
                            ts->position.y++;
                    }
                }
            }
            else
            {
                if (ts->position.y != pl.position.y)
                {
                    if (ts->position.y > pl.position.y)
                    {
                        ts->direction = 1;
                        if (!check_collision(1))
                            ts->position.y--;
                    }
                    else
                    {
                        ts->direction = 3;
                        if (!check_collision(3))
                            ts->position.y++;
                    }
                }
                else if (ts->position.x != pl.position.x)
                {
                    if (ts->position.x > pl.position.x)
                    {
                        ts->direction = 4;
                        if (!check_collision(4))
                            ts->position.x--;
                    }
                    else
                    {
                        ts->direction = 2;
                        if (!check_collision(2))
                        {
                            LOG(mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT);
                            ts->position.x++;
                        }
                    }
                }
            }
        }

        if (t.elapsed() >= rand() % 4 + 1 && ((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
        {
            pl_h->set_health(pl_h->get_health() - 1);
            t.start();
        }

        if (t.elapsed() >= rand() % 4 + 1 && pl.position.x == ts->position.x && pl.position.y == ts->position.y)
        {
            pl_h->set_health(pl_h->get_health() - 1);
            t.start();
        }

        if (m_health <= 0)
        {
            delete_self();
        }
    }

    void on_destroy()
    {
    }

private:
    int m_health;
    ui *m_healthbar;
    brown::Timer t;
    brown::Timer damage_t;
    brown::Timer t_move;
    player_controller *m_player;
};
/**/