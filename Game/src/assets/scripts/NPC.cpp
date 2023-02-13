#include "assets/scripts/NPC.hpp"

using namespace brown;

void NPC::on_interact(brown::event &e)
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
}

void NPC::on_create()
{
    ts = &get_component<transform>();
    ui_ = &get_component<ui>();

    m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, "NPC_" + std::to_string(m_entity.get_id()), NPC::on_interact));

    t.start();
    srand(time(NULL));
    dialog = dialogs[picked++];
}

void NPC::on_update()
{
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
        move(rand() % 4 + 1);
    }
}