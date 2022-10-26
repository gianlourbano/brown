#pragma once
#include "engine/math/mat.hpp"
#include "engine/math/vec2.hpp"
#include "engine/graphics/window/window.hpp"
#include <map>
#include "engine/debug/debugger.hpp"

#define TILE_SIZE 5

/**
 * @brief tile struct. Loaded from file.
 *
 */
struct tile
{
    int id;
    
    vec2 m_size = TILE_SIZE;
    mat<char> m_data = mat<char>(TILE_SIZE);

    std::string to_string()
    {
        std::string s = "";
        for (int i = 0; i < m_size.x; i++)
        {
            for (int j = 0; j < m_size.y; j++)
            {
                s += (char)m_data.at(i, j);
            }
            s += "\n";
        }
        return s;
    }
};

void print_tile(WINDOW *win, tile t, vec2 pos);

struct tileset
{
public:
    tileset(int size, std::string m_tilenames[]) : m_size(size)
    {
        for (int i = 0; i < size; i++)
        {
            tile t_i = {i};
            m_tiles.insert({i, t_i});
            std::string path = this->base_path + m_tilenames[i] + ".tile";
            m_tiles[i].m_data.load_from_file(path);
        }
    }

    tileset(int size, std::string base_path, std::string m_tilenames[])
    {
        this->base_path = base_path;
        tileset(size, m_tilenames);
    }

    int get_size() { return m_size; }

    tile operator[](size_t index)
    {
        return m_tiles[index];
    }

public:
    std::string base_path = "./src/assets/tiles/";
    std::map<size_t, tile> m_tiles;
    size_t m_size;
};

struct tilemap
{
public:
    void set_tile(size_t id, size_t x, size_t y)
    {
        m_data.set(id, x, y);
    }

    void load_from_file(std::string path)
    {
        std::ifstream f(m_tileset->base_path + path + ".tilemap");
        if (f.is_open())
        {
            for(int i = 0; i < m_x; i++) {
                for(int j = 0; j < m_y; j++) {
                    int id;
                    f >> id;
                    m_data.set(id, i, j);
                }
            }
        }
        else
        {
            LOG("Could not open file");
        }
    }

    tileset *m_tileset;
    int m_x = 10;
    int m_y = 10;

    mat<int> m_data = mat<int>(m_x, m_y);
};
