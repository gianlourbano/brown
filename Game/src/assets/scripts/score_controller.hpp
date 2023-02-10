#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "types.hpp"

class score_controller : public brown::scriptable_entity
{
public:
    void score_changed(brown::event& e)
    {
        m_score = e.get_param<int>(Events::Player::Score::SCORE);
    }
    void on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::SCORE,"scorebar", score_controller::score_changed));
        m_scorebar = &get_component<ui>();
        pl = static_cast<player_controller*>(m_state->find_entity("player").get_component<native_script>().instance);
        m_score = pl->get_score();
    }
    void on_update()
    {
        m_scorebar->text = "Score: "+ std::to_string(m_score);
    }

    void add_score(int score)
    {
        m_score += score;
    }

private:
    player_controller *pl = nullptr;
    ui *m_scorebar = nullptr;
    int m_score = 0;
};
