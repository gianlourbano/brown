#pragma once
#include <string>
#include <vector>
#include "../../../math/vec2.hpp"

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
};