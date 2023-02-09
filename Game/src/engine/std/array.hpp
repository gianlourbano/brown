#pragma once
#include <iostream>
#include <functional>

namespace brown::dt
{
    template <typename T, size_t N>
    class array
    {
    private:
        T m_data[N];

    public:
        constexpr array() = default;
        constexpr array(const array<T, N> &other) = default;
        constexpr array(array<T, N> &&other) noexcept = default;
        constexpr array(std::initializer_list<T> list)
        {
            size_t i = 0;
            for (auto &item : list)
            {
                m_data[i++] = item;
            }
        }

        constexpr array<T, N> &operator=(const array<T, N> &other) = default;
        constexpr array<T, N> &operator=(array<T, N> &&other) noexcept = default;

        constexpr T &operator[](size_t index)
        {
            return m_data[index];
        }

        constexpr const T &operator[](size_t index) const
        {
            return m_data[index];
        }

        constexpr T &at(size_t index)
        {
            return m_data[index];
        }

        constexpr const T &at(size_t index) const
        {
            return m_data[index];
        }

        constexpr T &front()
        {
            return m_data[0];
        }

        constexpr const T &front() const
        {
            return m_data[0];
        }

        constexpr T &back()
        {
            return m_data[N - 1];
        }

        constexpr const T &back() const
        {
            return m_data[N - 1];
        }

        constexpr T *data()
        {
            return m_data;
        }

        constexpr const T *data() const
        {
            return m_data;
        }

        constexpr bool empty() const
        {
            return N == 0;
        }

        constexpr size_t size() const
        {
            return N;
        }

        constexpr void fill(const T &value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] = value;
            }
        }

        constexpr void swap(array<T, N> &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                std::swap(m_data[i], other.m_data[i]);
            }
        }

        constexpr void sort()
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = i + 1; j < N; ++j)
                {
                    if (m_data[i] > m_data[j])
                    {
                        std::swap(m_data[i], m_data[j]);
                    }
                }
            }
        }

        constexpr void sort(std::function<bool(const T &, const T &)> compare)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = i + 1; j < N; ++j)
                {
                    if (compare(m_data[i], m_data[j]))
                    {
                        std::swap(m_data[i], m_data[j]);
                    }
                }
            }
        }

        constexpr void reverse()
        {
            for (size_t i = 0; i < N / 2; ++i)
            {
                std::swap(m_data[i], m_data[N - i - 1]);
            }
        }
        
    };
}