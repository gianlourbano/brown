#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/projectile.hpp"
#include "assets/scripts/player_controller.hpp"
#include "assets/scripts/projectile_boss.hpp"
#include "assets/scripts/ranged_enemy.hpp"

class boss_enemy : public scriptable_AI
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
        if (damage_t.elapsed() >= 1.5)
        {
            m_health--;
            damage_t.start();
            int row, col;
            /*
            auto bot = m_state->create_entity("bot");
            bot.add_component<transform>({ts->position.x+5,ts->position.y+3});
            brown::add_sprite({"a"}, "bot");
            bot.add_component<native_script>({}).bind<ranged_enemy>();
            bot.add_component<ui>({"", 0, true, true});
            */
        }
    }

    void on_create()
    {
        ts = &get_component<transform>();
        m_healthbar = &get_component<ui>();

        t.start();
        damage_t.start();
        t_attack.start();
        m_health = 5;

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
        m_healthbar->centered = true;

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
        }
        if(ts->position.y==pl.position.y){
            if(ts->position.x>pl.position.x){
                dir = 4;
            }else{
                dir = 2;
            }
        }
        int r = rand() % 4;
        if(t_attack.elapsed()>=9){
            if (can_shoot && r==0)
            {
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{pl.position.x,ts->position.y-11}, 3});
                proj1.add_component<sprite>({{0,0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{pl.position.x+3,ts->position.y-11}, 3});
                proj2.add_component<sprite>({{0,0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{pl.position.x-3,ts->position.y-11}, 3});
                proj3.add_component<sprite>({{0,0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());
            
               t_attack.start();
            }else if (can_shoot && r==1){
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{ts->position.x-35,pl.position.y}, 2});
                proj1.add_component<sprite>({{0,0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{ts->position.x-35,pl.position.y+2}, 2});
                proj2.add_component<sprite>({{0,0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{ts->position.x-35,pl.position.y-2}, 2});
                proj3.add_component<sprite>({{0,0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());
            
                t_attack.start();
            }else if (can_shoot && r==2){
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{pl.position.x,ts->position.y+11}, 1});
                proj1.add_component<sprite>({{0,0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{pl.position.x+3,ts->position.y+11}, 1});
                proj2.add_component<sprite>({{0,0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{pl.position.x-3,ts->position.y+11}, 1});
                proj3.add_component<sprite>({{0,0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());
            
                t_attack.start();
            }else{
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{ts->position.x+35,pl.position.y}, 4});
                proj1.add_component<sprite>({{0,0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{ts->position.x+35,pl.position.y+2}, 4});
                proj2.add_component<sprite>({{0,0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{ts->position.x+35,pl.position.y-2}, 4});
                proj3.add_component<sprite>({{0,0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());
            
                t_attack.start();
            }
            can_shoot = false;
        }
        if (m_health <= 0)
        {
            player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
            pl_h->kill();
            pl_h->kill();
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
    brown::Timer t_attack;
    player_controller *m_player;
    int m_proj_lifespan = 0;
    bool can_shoot = true;
};
