#pragma once

#include <iterator>

#include "memory/allocator.hpp"

namespace brown::dt
{
    template <typename T, typename alloc_ = brown::mem::allocator<T>>
    class vector
    {
    public:
        using allocator_type = alloc_;
        using iterator = T *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_iterator = const T *;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    protected:
        T *m_data = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 0;
        allocator_type m_allocator;

        void calc_cap()
        {
            if (m_size == 0)
                m_capacity = 1;
            else if (m_size == 1)
                m_capacity = 2;
            else
                m_capacity = m_size * 1.5;
        }

        void allocate_t(size_t size)
        {
            m_size = size;
            calc_cap();
            m_data = m_allocator.allocate(m_capacity);
        }

        void construct_t(size_t size, const T &value)
        {
            for (size_t i = 0; i < size; i++)
                m_allocator.construct(m_data + i, value);
        }

        void shrink(size_t size)
        {
            if (size < m_size)
            {
                size_t old_cap = m_capacity;
                m_size = size;
                calc_cap();
                T *new_data = m_allocator.allocate(m_capacity);
                for (size_t i = 0; i < m_size; i++)
                {
                    m_allocator.construct(new_data + i, m_data[i]);
                }
                m_allocator.deallocate(m_data, old_cap);
                m_data = new_data;
            }
        }
    public:
        void resize(size_t size, T value = T())
        {
            size_t old_size = size, old_cap = m_capacity, n_copies = size < m_size ? size : m_size;

            m_size = size;
            calc_cap();

            T *new_data = m_allocator.allocate(m_capacity);
            for (size_t i = 0; i < n_copies; i++)
            {
                m_allocator.construct(new_data + i, m_data[i]);
            }
            for (size_t i = n_copies; i < m_size; i++)
            {
                m_allocator.construct(new_data + i, value);
            }
            m_allocator.deallocate(m_data, old_cap);
            m_data = new_data;
        }

    public:
        vector(const allocator_type &alloc = allocator_type()) : m_allocator(alloc)
        {
            allocate_t(0);
        }

        vector(size_t size, const allocator_type &alloc = allocator_type()) : m_allocator(alloc)
        {
            allocate_t(size);
        }

        T &front()
        {
            return m_data[0];
        }

        const T &front() const
        {
            return m_data[0];
        }

        T &back()
        {
            return m_data[m_size - 1];
        }

        const T &back() const
        {
            return m_data[m_size - 1];
        }

        vector(size_t size, const T &value, const allocator_type &alloc = allocator_type()) : m_allocator(alloc)
        {
            allocate_t(size);
            construct_t(size, value);
        }

        vector(const vector &other) : m_allocator(other.m_allocator)
        {
            allocate_t(other.m_size);
            for(size_t i = 0; i < other.m_size; i++)
            {
                m_allocator.construct(m_data + i, other.m_data[i]);
            }
        }

        vector(vector &&other) noexcept : m_allocator(other.m_allocator)
        {
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        ~vector()
        {
            m_allocator.deallocate(m_data, m_capacity);
            m_data = nullptr;
        }

        template <typename... Args>
        void emplace_back(Args... args)
        {
            if (m_size >= m_capacity)
            {
                resize(m_size + 1, T(std::forward<T>(args)...));
            }
            else
                m_allocator.construct(m_data + m_size++, T(std::forward<T>(args)...));
        }

        void push_back(const T &value)
        {
            emplace_back(value);
        }

        void pop_back() {
            m_allocator.destroy(m_data + --m_size);
        }

        size_t erase(size_t index)
        {
            m_allocator.destroy(m_data + index);
            for (size_t k = index; k < m_size - 1; k++)
                m_data[k] = m_data[k + 1];

            if (m_size >= m_capacity * 2 / 3)
                m_size = m_size - 1;
            else
                shrink(m_size - 1);

            return index;
        }

        size_t erase(iterator i) {
            return erase(i - begin());
        }

        void clear()
        {
            shrink(0);
        }

        bool empty() const
        {
            return m_size == 0;
        }

        size_t size() const
        {
            return m_size;
        }

        size_t capacity() const
        {
            return m_capacity;
        }

        T* data() { return m_data;}
        const T* data() const { return m_data;}

        iterator begin() { return &m_data[0]; }
        const_iterator begin() const { return &m_data[0]; }
        iterator end() { return &m_data[m_size - 1] + 1; }
        const_iterator end() const { return &m_data[m_size - 1] + 1; }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_iterator cbegin() const { return &m_data[0]; }
        const_iterator cend() const { return &m_data[m_size - 1] + 1; }
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(begin());
        }

        //operators

        vector &operator=(const vector &other)
        {
            this->~vector();
            m_size = other.m_size;
            calc_cap();

            T* new_data = m_allocator.allocate(m_capacity);
            for(size_t i = 0; i < m_size; i++)
            {
                m_allocator.construct(new_data + i, other.m_data[i]);
            }
            m_data = new_data;
            return *this;
        }

        vector &operator=(vector &&other) noexcept
        {
            m_allocator.deallocate(m_data, m_capacity);
            m_allocator = other.m_allocator;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
            return *this;
        }

        T &operator[](size_t index)
        {
            return m_data[index];
        }

        const T &operator[](size_t index) const
        {
            return m_data[index];
        }
    };
}

#include "memory/allocator.cpp"