#pragma once
#include "../../../math/vec2.hpp"

//clips, playing, current, cyclic, time_step, offset, name, final
struct animation {
    int clips = 0;
    bool playing = false;
    int current = 0;
    bool cyclic = false;
    int time_step = 0;
    vec2 offset = 0;
    std::string name = "";
    bool final = false;
    bool has_finished = false;
};