#pragma once
#include "engine/brown.hpp"

class game_over : public brown::state
{
public:
    game_over(int final_score): m_final_score(final_score) {}

    void init(brown::engine*);
    void handle_events(brown::engine*);
    void update(brown::engine*);
    void draw(brown::engine*);

    void cleanup() {}
    void pause() {}
    void resume() {}

private:
    std::shared_ptr<brown::UI_system> m_ui_system;
    int m_final_score = 0;
};