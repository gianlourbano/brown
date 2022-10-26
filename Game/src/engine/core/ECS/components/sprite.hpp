#pragma once
#include <string>
#include <vector>
#include "../../../math/vec2.hpp"

enum Z_INDEX
{
    Z_1 = 1,
    Z_2 = 2,
    Z_3 = 4,
};

/**
 * @brief Sprite component.
 * 
 * @param size the size of the sprite.
 * @param sprite_name the name of the sprite.
 * @param offset the offset of the sprite in relation to the entity position.
 * 
 */
struct sprite
{
    vec2 size;
    std::string sprite_name;
    vec2 offset = 0;
    Z_INDEX z_index = Z_INDEX::Z_2;
};