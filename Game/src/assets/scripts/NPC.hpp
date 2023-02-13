#pragma once
#include "scriptable_AI.hpp"
#include "assets/scripts/projectile.hpp"
#include <random>
#include <time.h>
#include "types.hpp"
#include "engine/std/array.hpp"

using namespace brown;

dt::array<dt::array<std::string, 3>, 2> dialogs = {
    {{"You too in this place?",
      "I don't know how I got here",
      "I'm so scared"},
     {"Have you seen the other guy?",
      "He seems crazy...",
      "I'm scared too"}}};

int picked = 0;

class NPC : public scriptable_AI
{
public:
    void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(6))
        {
            if (curr_dialog < 3)
                curr_dialog++;
            if (curr_dialog == 3)
            {
                curr_dialog = 0;
            }
        }
    };

    void on_create()
    {
        ts = &get_component<transform>();
        ui_ = &get_component<ui>();

        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, "NPC_" + std::to_string(m_entity.get_id()), NPC::on_interact));

        t.start();
        srand(time(NULL));
        dialog = dialogs[picked++];
    }

    void on_update()
    {
        auto pl = m_state->find_entity("player").get_component<transform>();
        if (curr_dialog > 3)
        {
            curr_dialog = 0;
        }
        ui_->text = dialog[curr_dialog];

        if (is_player_in_range(6))
            ui_->is_visible = true;
        else
            ui_->is_visible = false;
        if (!is_player_in_range(6) && curr_dialog != 0)
        {
            curr_dialog = 0;
        }
        if (t.elapsed() >= rand() % 500 + 1)
        {
            if (ui_->is_visible)
            {
                if (ts->position.x != pl.position.x)
                {
                    if (ts->position.x > pl.position.x)
                    {
                        ts->direction = 1;
                        if (!check_collision(1))
                            ts->position.x--;
                    }
                    else
                    {
                        ts->direction = 3;
                        if (!check_collision(3))
                            ts->position.x++;
                    }
                }
                else if (ts->position.y != pl.position.y)
                {
                    if (ts->position.y > pl.position.y)
                    {
                        ts->direction = 4;
                        if (!check_collision(4))
                            ts->position.y--;
                    }
                    else
                    {
                        ts->direction = 2;
                        if (!check_collision(2))
                            ts->position.y++;
                    }
                }
            }
        }
    }

private:
    double speed = 3.0;
    brown::Timer t;

    unsigned int curr_dialog = 0;

    dt::array<std::string, 3> dialog;

    ui *ui_;
};