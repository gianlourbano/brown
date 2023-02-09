#pragma once
#include "vector.hpp"

namespace brown::dt
{
    template <typename T>
    class queue
    {
    public:
        queue() : m_data(), m_front(0), m_back(0) {}
        queue(const queue &other) : m_data(other.m_data), m_front(other.m_front), m_back(other.m_back) {}
        queue(queue &&other) noexcept : m_data(std::move(other.m_data)), m_front(other.m_front), m_back(other.m_back) {}
        queue &operator=(const queue &other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_data = other.m_data;
            m_front = other.m_front;
            m_back = other.m_back;
            return *this;
        }
        queue &operator=(queue &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            m_data = std::move(other.m_data);
            m_front = other.m_front;
            m_back = other.m_back;
            return *this;
        }
        ~queue() {m_data.~vector();}

        void push(const T &data)
        {
            m_data.push_back(data);
            ++m_back;
        }
        void pop()
        {
            ++m_front;
        }
        T &front()
        {
            return m_data[m_front];
        }
        const T &front() const
        {
            return m_data[m_front];
        }
        T &back()
        {
            return m_data[m_back - 1];
        }
        const T &back() const
        {
            return m_data[m_back - 1];
        }

        size_t size() const
        {
            return m_back - m_front;
        }
        bool empty() const
        {
            return m_front == m_back;
        }

    private:
        vector<T> m_data;
        size_t m_front;
        size_t m_back;
    };

}