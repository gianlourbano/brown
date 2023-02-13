#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "types.hpp"

class healtbar_controller : public brown::scriptable_entity
{
public:
    void health_changed(brown::event &e);
    void on_create();
    void on_update();
    void set_health(int health);

private:
    player_controller *pl = nullptr;
    ui *m_healthbar = nullptr;
    int m_health = 10;
};
