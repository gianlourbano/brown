#pragma once
#include "engine/brown.hpp"
#include <ncurses.h>

class scriptable_AI : public brown::scriptable_entity
{
public:

    virtual void on_interact(brown::event &e) {}


    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

public:
    virtual void on_hit() {};

    void on_create()
    {
        ts = &get_component<transform>();
        ui_ = &get_component<ui>();
        t.start();
        srand(time(NULL));
        
    }

    void on_update()
    {
        auto pl= m_state->find_entity("player").get_component<transform>();
        if (is_player_in_range(9))
            ui_->is_visible = true;
        else
            ui_->is_visible = false;
    }
protected:
    transform *ts;
    
private:
    brown::Timer t;
    double speed = 2.0;
    ui *ui_;
    vec2 pos;
    
};