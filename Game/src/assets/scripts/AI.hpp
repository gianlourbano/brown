#pragma once
#include "engine/brown.hpp"
#include <random>
#include <time.h>

class AI : public brown::scriptable_entity
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

    void move(int direction)
    {
        switch (direction)
        {
        case 1:
            ts->direction = 1;
            if (!check_collision(1))
                ts->position.y--;
            else
                ts->position.y++;
            break;
        case 2:
            ts->direction = 2;
            if (!check_collision(2))
                ts->position.x++;
            else
                ts->position.x--;
            break;
        case 3:
            ts->direction = 3;
            if (!check_collision(3))
                ts->position.y++;
            else
                ts->position.y--;
            break;
        case 4:
            ts->direction = 4;
            if (!check_collision(4))
                ts->position.x--;
            else
                ts->position.x++;
            break;
        }
    }

    void on_create()
    {
        ts = &get_component<transform>();
        ui_ = &get_component<ui>();
        t.start();
        srand(time(NULL));
    }

    void on_update()
    {
        if (is_player_in_range(6))
        {
            ui_->is_visible = true;
        } else ui_->is_visible = false;

        if (t.elapsed() >= rand() % (6 - 3 + 1) + 3)
        {
            move((rand() % 4) + 1);
            t.start();
        }
    }

private:
    double speed = 3.0;
    brown::Timer t;

    ui* ui_;
    transform *ts;
};