#include "scriptable_enemy.hpp"

void scriptable_enemy::on_hit(int damage) {
    int damage_dealt = damage-m_stats.defense * 0.5;
    if(damage_dealt >= 0)
        m_stats.health -= damage_dealt;
    else
        die();
}

void scriptable_enemy::die() {
    m_state->send_event(Events::Room::Enemy_killed);
    m_player->set_score(m_player->get_score() + m_stats.exp);
    delete_self();
}