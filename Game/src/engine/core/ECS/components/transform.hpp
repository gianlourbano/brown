#pragma once
#include "../../../math/vec2.hpp"

/**
 * @brief transform component.
 * 
 * @param position the position of the entity.
 * @param direction the direction of the entity.
 * @param z_index the z-index of the entity.
 * 
 */
struct transform {
    vec2 position = 0;
    int direction = 0;
    int z_index = 0;
};