#include "assets/scripts/boss.hpp"
#include "types.hpp"

void boss_enemy::on_create()
{
    scriptable_AI::on_create();
    m_healthbar = &get_component<ui>();

    t.start();
    damage_t.start();
    t_attack.start();
}

void boss_enemy::on_update()
{
    auto pl = m_state->find_entity("player").get_component<transform>();

    int i = 0;
    std::string hearts = "";
    for (; i < m_stats.health / 10; i++)
        hearts += "❤ ";
    m_healthbar->text = hearts;
    m_healthbar->centered = false;
    m_healthbar->offset = vec2{i, 2};

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
            proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj2 = m_state->create_entity();
            proj2.add_component<transform>({{pl.position.x + 3, ts->position.y - 11}, 3});
            proj2.add_component<sprite>({{0, 0}, "sprite2"});
            proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj3 = m_state->create_entity();
            proj3.add_component<transform>({{pl.position.x - 3, ts->position.y - 11}, 3});
            proj3.add_component<sprite>({{0, 0}, "sprite2"});
            proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            t_attack.start();
        }
        else if (can_shoot && r == 1)
        {
            brown::entity proj1 = m_state->create_entity();
            proj1.add_component<transform>({{ts->position.x - 35, pl.position.y}, 2});
            proj1.add_component<sprite>({{0, 0}, "sprite2"});
            proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj2 = m_state->create_entity();
            proj2.add_component<transform>({{ts->position.x - 35, pl.position.y + 2}, 2});
            proj2.add_component<sprite>({{0, 0}, "sprite2"});
            proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj3 = m_state->create_entity();
            proj3.add_component<transform>({{ts->position.x - 35, pl.position.y - 2}, 2});
            proj3.add_component<sprite>({{0, 0}, "sprite2"});
            proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            t_attack.start();
        }
        else if (can_shoot && r == 2)
        {
            brown::entity proj1 = m_state->create_entity();
            proj1.add_component<transform>({{pl.position.x, ts->position.y + 11}, 1});
            proj1.add_component<sprite>({{0, 0}, "sprite2"});
            proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj2 = m_state->create_entity();
            proj2.add_component<transform>({{pl.position.x + 3, ts->position.y + 11}, 1});
            proj2.add_component<sprite>({{0, 0}, "sprite2"});
            proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj3 = m_state->create_entity();
            proj3.add_component<transform>({{pl.position.x - 3, ts->position.y + 11}, 1});
            proj3.add_component<sprite>({{0, 0}, "sprite2"});
            proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            t_attack.start();
        }
        else
        {
            brown::entity proj1 = m_state->create_entity();
            proj1.add_component<transform>({{ts->position.x + 35, pl.position.y}, 4});
            proj1.add_component<sprite>({{0, 0}, "sprite2"});
            proj1.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj1.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj2 = m_state->create_entity();
            proj2.add_component<transform>({{ts->position.x + 35, pl.position.y + 2}, 4});
            proj2.add_component<sprite>({{0, 0}, "sprite2"});
            proj2.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj2.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            brown::entity proj3 = m_state->create_entity();
            proj3.add_component<transform>({{ts->position.x + 35, pl.position.y - 2}, 4});
            proj3.add_component<sprite>({{0, 0}, "sprite2"});
            proj3.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj3.add_component<native_script>({}).bind<projectile_boss>(m_entity.get_id(), m_stats.damage);

            t_attack.start();
        }
        can_shoot = false;
    }
}
void boss_enemy::on_destroy()
{
    m_state->send_event(Events::Room::World_cleared);
}
