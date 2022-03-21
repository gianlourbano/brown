#pragma once
#include "engine/brown.hpp"

class player_controller : public brown::scriptable_entity
{
public:
    void on_create()
    {
        health = 100;
        ts = &get_component<transform>();
        anim = &get_component<animation>();
    }

    void on_update()
    {
        if (brown::KEY_PRESSED == 'a')
            ts->position.x--;
        else if (brown::KEY_PRESSED == 'd')
            ts->position.x++;

        if (brown::KEY_PRESSED == 'w')
            ts->position.y--;
        else if (brown::KEY_PRESSED == 's')
            ts->position.y++;

        if(brown::KEY_PRESSED == 'h')
            anim->playing = true;

        if (brown::KEY_PRESSED == 't')
            delete_self();
    }

    void on_destroy() {
        endwin();
    }

private:
    transform *ts = nullptr;
    animation *anim = nullptr;
    int health;
};