#pragma once
#include "brown.hpp"

vec2 forces[4] = {
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

        return chars[dir - 1] != ' ';
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
        if (lifetime != 0)
        {

            ts->position += force;
            lifetime--;
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

    void on_destroy() {
        ts = nullptr;
        anim = nullptr;
    }

private:
    int lifetime;
    bool has_finished = false;
    vec2 force;
    int tot;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
};