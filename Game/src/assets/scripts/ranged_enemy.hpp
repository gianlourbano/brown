#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/projectile.hpp"
#include "assets/scripts/player_controller.hpp"

class ranged_enemy : public scriptable_AI
{
public:
    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y - 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x - 1) & A_CHARTEXT};

        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

    void on_hit()
    {
        if (damage_t.elapsed() >= 0.5)
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
        proj_anim = {
            "animated1",
            2,
            5,
            5,
            false,
            true};
    };
    void on_update()
    {
        auto pl = m_state->find_entity("player").get_component<transform>();
        player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        std::string hearts = "";
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;
        
        if (m_proj_lifespan == 0)
            can_shoot = true;

        if (m_proj_lifespan != 0)
            m_proj_lifespan--;
        int dir;
        if(ts->position.x==pl.position.x){
            if(ts->position.y>pl.position.y){
                dir = 1;
            }else{
                dir = 3;
            }
        }if(ts->position.y==pl.position.y){
            if(ts->position.x>pl.position.x){
                dir = 4;
            }else{
                dir = 2;
            }
            }
        if (can_shoot &&(ts->position.x==pl.position.x||ts->position.y==pl.position.y) && is_player_in_range(8))
        {
            brown::entity proj = m_state->create_entity();
            proj.add_component<transform>({ts->position, dir});
            proj.add_component<sprite>({{2, 2}, "sprite2"});
            proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj.add_component<native_script>({}).bind<projectile>(m_entity.get_id());

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
        
        if (is_player_in_range(10) && t_move.elapsed() >= 0.5 && !((pl.position.x + 1 == ts->position.x || pl.position.x - 1 == ts->position.x) && pl.position.y == ts->position.y || pl.position.x == ts->position.x && (pl.position.y + 1 == ts->position.y || pl.position.y - 1 == ts->position.y)))
        {
            t_move.start();
            int r = rand()%2 +1;
            if(r==1){
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
            }else{
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
                }else if (ts->position.x != pl.position.x)
                {
                    if (ts->position.x > pl.position.x)
                    {
                        ts->direction =4;
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
        if (m_health <= 0)
        {
            player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
            pl_h->kill();
            delete_self();
        }
    }
    void on_destroy()
    {
    }

private:
    int m_health;
    ui *m_healthbar;
    animation proj_anim;
    brown::Timer t;
    brown::Timer damage_t;
    brown::Timer t_move;
    player_controller *m_player;
    int m_proj_lifespan = 0;
    bool can_shoot = true;
};
