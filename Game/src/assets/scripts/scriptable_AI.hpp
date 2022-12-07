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
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 2) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 2, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

public:
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
        {
            ui_->is_visible = true;
        }
        else
            ui_->is_visible = false;

        if (t.elapsed() >= rand() % 500 + 1)
        {
        if (ui_->is_visible){
             if(ts->position.x!=pl.position.x)
            {
                if(ts->position.x>pl.position.x ){
                    ts->direction = 4;
                    if(!check_collision(4))
                        ts->position.x--;              
                }else {
                    ts->direction = 2;
                    if(!check_collision(2))
                        ts->position.x++;
                }  
            }
            else if (ts->position.y!=pl.position.y)
            {
                if(ts->position.y>pl.position.y){
                    ts->direction = 1;
                    if (!check_collision(1)) 
                        ts->position.y--;

                }else{
                    ts->direction = 3;
                    if (!check_collision(3))
                        ts->position.y++;
                
                }
            }}else{
                //Cancello una vita al player
            }
        }
    }
protected:
    transform *ts;
private:
    double speed = 2.0;
    brown::Timer t;
    ui *ui_;
    vec2 pos;
    
};