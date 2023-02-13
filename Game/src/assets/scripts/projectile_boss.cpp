#include "assets/scripts/projectile_boss.hpp"
    
    bool projectile_boss::check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 2) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 2, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        return chars[dir - 1] == 'a' || chars[dir - 1] == '%' || chars[dir - 1] == '#' || chars[dir - 1] == 'x';
    }
    void projectile_boss::on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        force = forces[ts->direction - 1];
        t_end.start();
    }

    void projectile_boss::on_update()
    {
        if (!check_collision(ts->direction))
        {

            if (check_collision(ts->direction))
            {
                has_finished = true;
            }
            else
            {
                ts->position += force;
            }
        }
        else
        {
            force = 0;
            has_finished = true;
        }

        if(has_finished&&!timer_started){
            timer_started = true;
            t_end.start();
        }
        if (has_finished)
        {
            for (auto &e : m_state->get_entities())
            {
                if (m_creator_id != e.get_id()&& e.get_id() != this->m_entity.get_id())
                {
                    auto &ts_ = e.get_component<transform>();
                    float dist = distance(ts->position, ts_.position);
                    if (dist <= 2 && dist > 0)
                    {
                        
                        scriptable_AI *script = dynamic_cast<scriptable_AI *>(e.get_component<native_script>().instance);
                        
                        if (script != nullptr)
                        {
                            script->on_hit();
                        }
                    }
                }
            }
            anim->play("explode", [this]()
                       {LOG("projectile deleted");this->delete_self(); });
            if(t_end.elapsed()>=0.3){
                this->delete_self();
            }
        }
        

    }

    void projectile_boss::on_destroy()
    {
        ts = nullptr;
        anim = nullptr;
    }