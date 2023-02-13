#pragma once
#include "scriptable_AI.hpp"
#include "assets/scripts/projectile.hpp"
#include <random>
#include <time.h>
#include "types.hpp"
#include "engine/std/array.hpp"

using namespace brown;

static int picked = 0;

static dt::array<dt::array<std::string, 3>, 2> dialogs = {
    {{"You too in this place?",
      "I don't know how I got here",
      "I'm so scared"},
     {"Have you seen the other guy?",
      "He seems crazy...",
      "I'm scared too"}}};

class NPC : public scriptable_AI
{
public:
    void on_interact(brown::event &e);
    void on_create();
    void on_update();

private:
    double speed = 3.0;
    brown::Timer t;
    unsigned int curr_dialog = 0;
    dt::array<std::string, 3> dialog;
    ui *ui_;
};