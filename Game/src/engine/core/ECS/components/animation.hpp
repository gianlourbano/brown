#include "../../../math/vec2.hpp"

struct animation {
    int clips = 0;
    bool playing = false;
    int current = 0;
    bool cyclic = false;
    int time_step = 0;
    vec2 offset = 0;
    std::string name = "";
    bool final = false;
};