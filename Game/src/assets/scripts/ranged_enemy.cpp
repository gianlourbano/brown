#include "ranged_enemy.hpp"

void ranged_enemy::on_create()
{
    scriptable_AI::on_create();
    m_healthbar = &get_component<ui>();

    t.start();
    damage_t.start();
    t_move.start();
}

void ranged_enemy::on_update()
{
    auto pl = m_state->find_entity("player").get_component<transform>();

    std::string hearts = "";
    for (int i = 0; i < m_stats.health / 10; i++)
        hearts += "❤ ";
    m_healthbar->text = hearts;

    if (m_proj_lifespan == 0)
        can_shoot = true;

    if (m_proj_lifespan != 0)
        m_proj_lifespan--;
    int dir;
    if (ts->position.x == pl.position.x)
    {
        if (ts->position.y > pl.position.y)
        {
            dir = 1;
        }
        else
        {
            dir = 3;
        }
    }
    if (ts->position.y == pl.position.y)
    {
        if (ts->position.x > pl.position.x)
        {
            dir = 4;
        }
        else
        {
            dir = 2;
        }
    }
    if (can_shoot && (ts->position.x == pl.position.x || ts->position.y == pl.position.y) && is_player_in_range(8))
    {
        brown::entity proj = m_state->create_entity();
        proj.add_component<transform>({ts->position, dir});
        proj.add_component<sprite>({{2, 2}, "sprite2"});
        proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
        proj.add_component<native_script>({}).bind<projectile>(m_entity.get_id(), m_stats.damage);

        can_shoot = false;

        int lifetime = 10;

        switch (dir)
        {
        case 1:
        case 3:
            lifetime /= 2;
            break;
        }
        m_proj_lifespan = lifetime + proj_anim.clips * proj_anim.time_step;
    }

    if (!is_player_in_range(10) && t_move.elapsed() >= 0.5 && !((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
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
                        ts->position.x++;
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
                        ts->position.x++;
                }
            }
        }
    }
}
void ranged_enemy::on_destroy()
{
}
