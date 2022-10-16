#pragma once
#include "../../../math/vec2.hpp"

/**
 * @brief Basic structure for animation clips.
 * 
 * @param name the name of the animation from the file.
 * @param offset the offset of the animation in relation to the sprite.
 * @param clips the number of clips of the animation.
 * @param time_step the number of milliseconds of each frame.
 * @param cyclic wether the animation must repeat itself or not.
 * @param final wether the final clip should be set as the entity sprite.
 */
struct animation {
    std::string name = "";
    vec2 offset = 0;

    int clips = 0;
    int time_step = 0;
    bool cyclic = false;
    bool final = false;

    //flags for animation system
    bool is_reversed = false;
    bool playing = false;
    bool has_finished = false;
    int current = 0;
};

