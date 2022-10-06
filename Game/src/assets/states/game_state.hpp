#pragma once
#include "engine/brown.hpp"

class game_state : public brown::state
{

public:

    void init(brown::engine *game) {}

    void resume() {}
    void pause() {}
    void cleanup() {}

    void update(brown::engine *game) {}
    void handle_events(brown::engine *game) {}
    void draw(brown::engine *game) {}

    static game_state *instance()
    {
        return &m_game_state;
    }

protected:
    game_state() {}

private:
    static game_state m_game_state;
};