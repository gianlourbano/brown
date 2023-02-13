#pragma once
#include "engine/brown.hpp"
#include "player_controller.hpp"
#include "types.hpp"

class score_controller : public brown::scriptable_entity
{
public:
    void score_changed(brown::event& e);
    void on_create();
    void on_update();
    void add_score(int score);

private:
    player_controller *pl = nullptr;
    ui *m_scorebar = nullptr;
    int m_score = 0;
};
