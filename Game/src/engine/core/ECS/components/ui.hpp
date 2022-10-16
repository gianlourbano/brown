#pragma once
#include <string>

/**
 * @brief Basic UI component.
 * 
 * @param text the text of the component.
 * @param is_visible wether the component is visible or not.
 */
struct ui {
    std::string text = "";
    bool is_visible = true;
};