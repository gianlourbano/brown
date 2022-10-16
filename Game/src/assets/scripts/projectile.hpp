#pragma once
#include "brown.hpp"

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

        return chars[dir - 1] != ' ';
    }
    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        lifetime = 10;

        tot = lifetime + anim->current_anim->clips * anim->current_anim->time_step;

        switch (ts->direction)
        {
        case 1:
            force = {0, -1};
            lifetime /= 2;
            break;
        case 2:
            force = {1, 0};
            break;
        case 3:
            force = {0, 1};
            lifetime /= 2;
            break;
        case 4:
            force = {-1, 0};
            break;
        }
    }

    void on_update()
    {
        tot--;
        if (lifetime != 0)
        {
            if (!check_collision(ts->direction))
            {
                ts->position += force;
                lifetime--;
            }
            else
            {
                tot -= lifetime;
                lifetime = 0;
                has_finished = true;
            }
        }
        else
        {
            has_finished = true;
        }

        if (has_finished)
        {
            anim->play("explode", [this]()
                       {LOG("projectile deleted");this->delete_self(); });
        }

        if (tot == 0)
        {
            this->delete_self();
        }
    }

private:
    int lifetime;
    bool has_finished = false;
    vec2 force;
    int tot;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
};