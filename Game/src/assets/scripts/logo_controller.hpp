#pragma once
#include "engine/brown.hpp"

class logo_controller : public brown::scriptable_entity
{
public:
    void on_create();

    void on_update();

private:
    transform *ts;
    int m_counter = 0;

    brown::Timer m_timer;
};