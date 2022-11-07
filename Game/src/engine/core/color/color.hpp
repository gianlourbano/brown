#pragma once
#include <string>

namespace brown::colors {
    
    /**
     * @brief Starts color mode for the application.
     * 
     * After calling this a palette and a character map should be loaded from the /assets/colors/ folder.
     */
    void start_colors();

    void init_color_from_rgb(short id, short r, short g, short b);

    void make_pair(short pair_id, short color_A_id, short color_B_id);

    /**
     * @brief Loads a palette from a file.
     * 
     * The default directory from which the file is loaded is /assets/colors/.
     * The file should be a text file with the following format:
     *      color_name r g b
     * 
     * @param palette The name of the file to load the palette from.
     *
     */
    void init_palette_from_file(std::string palette);

    /**
     * @brief Loads a character map from a file.
     * 
     * The default directory from which the file is loaded is /assets/colors/.
     * The file should be a text file with the following format:
     *     color_name char
     * 
     * @param color_map The name of the file to load the character map from.
     *
     */
    void init_color_map_from_file(std::string map);

    int add_custom_pair(short color_A_id, short color_B_id);
    int add_custom_color(short r, short g, short b);
}