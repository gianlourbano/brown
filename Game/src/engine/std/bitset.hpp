#pragma once
#include <unistd.h>
#include <iostream>
//#include "string.hpp"
#include <string>
using std::string;

namespace brown::dt
{
    template <size_t _Size>
    class bitset
    {
    private:
        unsigned int m_data = 0;

    public:
        constexpr bitset() = default;
        constexpr bitset(const unsigned int &data) : m_data(data) {}
        constexpr bitset(const bitset<_Size> &other) = default;
        constexpr bitset(bitset<_Size> &&other) noexcept = default;

        constexpr bitset<_Size> &operator=(const bitset<_Size> &other) = default;
        constexpr bitset<_Size> &operator=(bitset<_Size> &&other) noexcept = default;

        constexpr bool operator[](size_t index) const
        {
            return get(index);
        }

        constexpr bool get(size_t index) const
        {
            return (m_data & (1 << index)) != 0;
        }

        constexpr void set(size_t index, bool value = true)
        {
            if (value)
                m_data |= (1 << index);
            else
                m_data &= ~(1 << index);
        }

        constexpr void clear(size_t index)
        {
            m_data &= ~(1 << index);
        }

        constexpr void reset()
        {
            m_data = 0;
        }

        constexpr void flip(size_t index)
        {
            m_data ^= (1 << index);
        }

        constexpr bitset<_Size> operator|(const bitset<_Size> &other) const
        {
            return bitset<_Size>(m_data | other.m_data);
        }

        constexpr bitset<_Size> operator&(const bitset<_Size> &other) const
        {
            return bitset<_Size>(m_data & other.m_data);
        }

        constexpr bitset<_Size> operator^(const bitset<_Size> &other) const
        {
            return bitset<_Size>(m_data ^ other.m_data);
        }

        constexpr bitset<_Size> operator~() const
        {
            return bitset<_Size>(~m_data);
        }

        constexpr bitset<_Size> &operator|=(const bitset<_Size> &other)
        {
            m_data |= other.m_data;
            return *this;
        }

        constexpr bitset<_Size> &operator&=(const bitset<_Size> &other)
        {
            m_data &= other.m_data;
            return *this;
        }

        constexpr bitset<_Size> &operator^=(const bitset<_Size> &other)
        {
            m_data ^= other.m_data;
            return *this;
        }

        constexpr bool operator==(const bitset<_Size> &other) const
        {
            return m_data == other.m_data;
        }

        constexpr bool operator!=(const bitset<_Size> &other) const
        {
            return m_data != other.m_data;
        }

        friend std::ostream &operator<<(std::ostream &stream, const bitset<_Size> &bitset)
        {
            for (size_t i = 0; i < _Size; i++)
            {
                stream << bitset[i];
            }
            return stream;
        }

        string to_string() const
        {
            string result = "";
            for (size_t i = 0; i < _Size; i++)
            {
                result += std::to_string(get(i));
            }
            return result;
        }
    };
}