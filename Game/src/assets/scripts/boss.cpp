#include "assets/scripts/boss.hpp"


    bool boss_enemy::check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y - 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x - 1) & A_CHARTEXT};

        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

    void boss_enemy::on_create()
    {
        scriptable_enemy::on_create();
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
    void boss_enemy::on_update()
    {
        auto pl = m_state->find_entity("player").get_component<transform>();
        player_controller *pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        std::string hearts = " ";
        int i = 0;
        for (i = 0; i < m_health / 10; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;
        m_healthbar->offset = vec2{-i / 2, 0};
        m_healthbar->centered = false;

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
        /*if (t.elapsed()>1.7){
            while (!check_collision(dir))
            {
                move(dir);
            }   
        t.start();
        }
        */
        int r = rand() % 4;
        if (t_attack.elapsed() >= 9)
        {
            if (can_shoot && r == 0)
            {
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{pl.position.x, ts->position.y - 11}, 3});
                proj1.add_component<sprite>({{0, 0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{pl.position.x + 3, ts->position.y - 11}, 3});
                proj2.add_component<sprite>({{0, 0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{pl.position.x - 3, ts->position.y - 11}, 3});
                proj3.add_component<sprite>({{0, 0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                t_attack.start();
            }
            else if (can_shoot && r == 1)
            {
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{ts->position.x - 35, pl.position.y}, 2});
                proj1.add_component<sprite>({{0, 0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{ts->position.x - 35, pl.position.y + 2}, 2});
                proj2.add_component<sprite>({{0, 0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{ts->position.x - 35, pl.position.y - 2}, 2});
                proj3.add_component<sprite>({{0, 0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                t_attack.start();
            }
            else if (can_shoot && r == 2)
            {
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{pl.position.x, ts->position.y + 11}, 1});
                proj1.add_component<sprite>({{0, 0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{pl.position.x + 3, ts->position.y + 11}, 1});
                proj2.add_component<sprite>({{0, 0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{pl.position.x - 3, ts->position.y + 11}, 1});
                proj3.add_component<sprite>({{0, 0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                t_attack.start();
            }
            else
            {
                brown::entity proj1 = m_state->create_entity();
                proj1.add_component<transform>({{ts->position.x + 35, pl.position.y}, 4});
                proj1.add_component<sprite>({{0, 0}, "sprite2"});
                proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj2 = m_state->create_entity();
                proj2.add_component<transform>({{ts->position.x + 35, pl.position.y + 2}, 4});
                proj2.add_component<sprite>({{0, 0}, "sprite2"});
                proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                brown::entity proj3 = m_state->create_entity();
                proj3.add_component<transform>({{ts->position.x + 35, pl.position.y - 2}, 4});
                proj3.add_component<sprite>({{0, 0}, "sprite2"});
                proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
                proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id());

                t_attack.start();
            }
            can_shoot = false;
        }
        if (m_health <= 0)
        {
            m_player->set_score(m_player->get_score() + exp);
            delete_self();
        }
    }
    void boss_enemy::on_destroy()
    {
    }
