#pragma once
#include <string>
#include "engine/math/vec2.hpp"

/**
 * @brief Basic UI component.
 *
 * @param text the text of the component.
 * @param offset the offset of the text.
 * @param is_visible wether the component is visible or not.
 * @param centered wether the text is centered or not.
 *
 */
struct ui
{
public:
    std::string text = "";
    vec2 offset = 0;
    bool is_visible = true;
    bool centered = false;
};