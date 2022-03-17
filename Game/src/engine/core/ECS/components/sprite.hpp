#pragma once
#include <string>
#include <vector>
#include "../../../math/vec2.hpp"

using sprite_data = std::vector<std::string>;

struct sprite
{
    vec2 size;
    std::string sprite_name;
};