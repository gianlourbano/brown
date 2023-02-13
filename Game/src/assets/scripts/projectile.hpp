#pragma once
#include "brown.hpp"
#include "scriptable_enemy.hpp"

static vec2 forces[4] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}};

class projectile : public brown::scriptable_entity
{
public:
    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 2) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 2, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        return chars[dir - 1] == 'a'|| chars[dir - 1] == 'b' || chars[dir - 1] == '%' || chars[dir - 1] == '#' || chars[dir - 1] == 'x';
    }
    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        lifetime = 10;

        force = forces[ts->direction - 1];

        switch (ts->direction)
        {
        case 1:
        case 3:
            lifetime /= 2;
            break;
        }
        tot = lifetime + anim->current_anim->clips * anim->current_anim->time_step;
    }

    void on_update()
    {
        tot--;
        if (lifetime != 0 && !check_collision(ts->direction))
        {

            if (check_collision(ts->direction))
            {
                tot -= lifetime;
                lifetime = 0;
                has_finished = true;
            }
            else
            {
                ts->position += force;
                lifetime--;
            }
        }
        else
        {
            force = 0;
            has_finished = true;
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
                            script->on_hit(damage);
                        }
                    }
                }
            }

            anim->play("explode", [this]()
                       {LOG("projectile deleted");this->delete_self(); });
        }

        if (tot == 0)
        {
            this->delete_self();
        }
    }

    void on_destroy()
    {
        ts = nullptr;
        anim = nullptr;
    }

    int get_lifetime()
    {
        return lifetime;
    }

    projectile(entity_id creator, int damage = 0) : m_creator_id(creator), damage(damage) {}

private:
    int lifetime;
    bool has_finished = false;
    vec2 force;
    int tot;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;

    int damage = 0;
    entity_id m_creator_id;
};