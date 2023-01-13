#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/player_controller.hpp"

class scriptable_enemy : public scriptable_AI
{
public:
    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y - 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x - 1) & A_CHARTEXT};

        // return !(chars[dir - 1] == ' ' || (chars[dir - 1] <= 'z' && chars[dir - 1] >= 'a'));
        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

    void on_hit()
    {
        if (damage_t.elapsed() >= 0.7)
        {
            m_health--;
            damage_t.start();
        }
    }

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
        std::string hearts = "";
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;
        if (t.elapsed() >= rand() % 4 + 1 && ((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
        {
            pl_h->set_health(pl_h->get_health() - 1);
            t.start();
        }

        if (is_player_in_range(10) && t_move.elapsed() >= 0.5 && !((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
        {
            t_move.start();
            if (ts->position.x != pl.position.x)
            {
                if (ts->position.x > pl.position.x)
                {
                    ts->direction = 3;
                    if (!check_collision(3))
                        ts->position.x--;
                }
                else
                {
                    ts->direction = 1;
                    if (!check_collision(1))
                        ts->position.x++;
                }
            }
            else if (ts->position.y != pl.position.y)
            {
                if (ts->position.y > pl.position.y)
                {
                    ts->direction = 4;
                    if (!check_collision(4))
                        ts->position.y--;
                }
                else
                {
                    ts->direction = 2;
                    if (!check_collision(2))
                        ts->position.y++;
                }
            }
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
