#include "assets/scripts/score_controller.hpp"


    void score_controller::score_changed(brown::event& e)
    {
        m_score = e.get_param<player_data>(Events::Player::Data::DATA).score;
    }
    void score_controller::on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::DATA,"scorebar", score_controller::score_changed));
        m_scorebar = &get_component<ui>();
        pl = static_cast<player_controller*>(m_state->find_entity("player").get_component<native_script>().instance);
        m_score = pl->get_score();
    }
    void score_controller::on_update()
    {
        m_scorebar->text = "Score: "+ std::to_string(m_score);
    }

    void score_controller::add_score(int score)
    {
        m_score += score;
    }
