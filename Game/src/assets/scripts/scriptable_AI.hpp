#pragma once
#include "engine/brown.hpp"
#include <ncurses.h>

class player_controller;

class scriptable_AI : public brown::scriptable_entity
{
public:

    virtual void on_interact(brown::event &e) {}
    virtual void on_hit(int) {}

    bool check_collision(int dir);
    void move(int dir);

    void on_create();

protected:
    transform *ts;
    
    double speed = 2.0;
    vec2 pos;
    player_controller* m_player;
};