#pragma once
#include "scriptable_AI.hpp"
#include "assets/scripts/projectile.hpp"
#include <random>
#include <time.h>
#include "types.hpp"

std::array<std::array<std::string, 3>, 2> dialogs = {
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

        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, NPC::on_interact));

        t.start();
        srand(time(NULL));
        dialog = dialogs[picked++];
    }

    void on_update()
    {
        

        if (curr_dialog > 3)
        {
            curr_dialog = 0;
        }
        ui_->text = dialog[curr_dialog];

        if (is_player_in_range(6))
        {

            ui_->is_visible = true;
        }
        else
            ui_->is_visible = false;

        if (t.elapsed() >= rand() % 4 + 3)
        {
            move((rand() % 4) + 1);
            t.start();
        }

        if (!is_player_in_range(6) && curr_dialog != 0)
        {
            curr_dialog = 0;
        }
    }

private:
    double speed = 3.0;
    brown::Timer t;

    unsigned int curr_dialog = 0;

    std::array<std::string, 3> dialog;

    ui *ui_;
    
    
};