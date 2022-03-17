#pragma once
#include "../../../math/vec2.hpp"

struct transform {
    vec2 position = 0;
    vec2 scale = 0;
    int z_index = 0;
    int direction = 0;
};