#include "projectile.hpp"
#include "player_controller.hpp"

void player_controller::shoot(int dir)
{
    if (can_shoot)
    {
        brown::entity proj = m_state->create_entity();
        proj.add_component<transform>({ts->position, dir});
        proj.add_component<sprite>({{2, 2}, "sprite2"});
        proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
        proj.add_component<native_script>({}).bind<projectile>(m_entity.get_id(), this->m_data.attack_damage);

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
}