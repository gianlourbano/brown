#pragma once
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "engine/std/vector.hpp"

template <typename T>
class mat
{
public:
    mat(int size) : mat(size, size) {}

    mat(int x, int y): m_x(x), m_y(y)
    {
        m_data.resize(m_x*m_y);
    }
    mat(T *t, int x, int y): m_x(x), m_y(y)
    {
        for (int i = 0; i < m_x * m_y; i++)
        {
            m_data.push_back(t[i]);
        }
    }

    void set_all(brown::dt::vector<T>& data)
    {
        for(int i = 0; i < m_x * m_y; i++)
        {
            m_data[i] = data[i];
        }
    }

    void set(T t, size_t x, size_t y)
    {
        m_data[x * m_y + y] = t;
    }

    T& at(int x, int y)
    {
        return m_data[x + y * m_x];
    }

    const T& at(int x, int y) const {
        return m_data[x + y * m_x];
    }
    
    void load_from_file(std::string path)
    {
        std::fstream f = std::fstream(path, std::ios::in);
        for (int i = 0; i < m_x; i++)
        {
            for (int j = 0; j < m_y; j++)
            {
                T c;
                f >> c;
                m_data[i * m_y + j] = (T)(c);
            }
        }
        f.close();
    } 

    void rotate() {
        int size = m_x*m_y;
        int layer_count = size/2;

        for(int layer = 0; layer < layer_count; layer++) {
            int first = layer;
            int last = size - 1 - layer;

            for(int i = first; i < last; i++) {
                int offset = i - first;
                T top = m_data[first * m_y + i];
                m_data[first * m_y + i] = m_data[(last - offset) * m_y + first];
                m_data[(last - offset) * m_y + first] = m_data[last * m_y + last - offset];
                m_data[last * m_y + last - offset] = m_data[i * m_y + last];
                m_data[i * m_y + last] = top;
            }
        }
    }

    T& operator[] (size_t index)
    {
        return m_data[index];
    }

    const T& operator[] (size_t index) const
    {
        return m_data[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const mat &m)
    {
        for (int i = 0; i < m.m_x*m.m_y; i++)
        {
            os << m.m_data[i] << " ";
            if (i % m.m_x == m.m_x - 1)
            {
                os << std::endl;
            }
        }
        return os;
    }

    ~mat()
    {
        for(auto& i : m_data) {
            i.~T();
        }
        m_data.clear();
    }

private:
    int m_x;
    int m_y;
    brown::dt::vector<T> m_data;
};