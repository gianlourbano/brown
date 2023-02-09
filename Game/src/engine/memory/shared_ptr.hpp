#pragma once
#include <utility>

namespace brown::mem
{
    /**
     * @brief Shared pointer class.
     *
     * A shared pointer is a wrapper around a pointer that keeps track of how many references there are to the pointer.
     * When the last reference is destroyed, the pointer is deleted.
     *
     * @tparam T the type of the pointer
     *
     */
    template <typename T>
    class shared_ptr
    {
    public:
        using element_type = T;

        shared_ptr() : m_data(nullptr), m_count(nullptr) {}
        explicit shared_ptr(T *data) : m_data(data), m_count(new size_t(1)) {}
        template <typename U>
        shared_ptr(U *other) : m_data(static_cast<T *>(other)), m_count(new size_t(1)) {}
        shared_ptr(const shared_ptr &other) : m_data(other.m_data), m_count(other.m_count)
        {
            if (m_count != nullptr)
            {
                ++(*m_count);
            }
        }
        shared_ptr(shared_ptr &&other) noexcept : m_data(other.m_data), m_count(other.m_count)
        {
            other.m_data = nullptr;
            other.m_count = nullptr;
        }

        template <typename U>
        shared_ptr(const shared_ptr<U> &other) : m_data(static_cast<T *>(other.data())), m_count(other.count())
        {
            if (m_count != nullptr)
            {
                ++(*m_count);
            }
        }

        template <typename U>
        shared_ptr(shared_ptr<U> &&other) noexcept : m_data(static_cast<T *>(other.data())), m_count(other.count())
        {
            other.m_data = nullptr;
            other.m_count = nullptr;
        }

        template <typename U>
        shared_ptr<T> &operator=(const shared_ptr<U> &other)
        {
            if (m_count != nullptr)
            {
                --(*m_count);
                if (*m_count == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }

            m_data = static_cast<T *>(other.m_data);
            m_count = other.m_count;

            if (m_count != nullptr)
            {
                ++(*m_count);
            }

            return *this;
        }

        template <typename U>
        shared_ptr<T> &operator=(shared_ptr<U> &&other) noexcept
        {
            if (m_count != nullptr)
            {
                --(*m_count);
                if (*m_count == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }

            m_data = static_cast<T *>(other.m_data);
            m_count = other.m_count;

            other.m_data = nullptr;
            other.m_count = nullptr;

            return *this;
        }

        shared_ptr &operator=(const shared_ptr &other)
        {
            if (this == &other)
            {
                return *this;
            }

            if (m_count != nullptr)
            {
                if (--(*m_count) == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }

            m_data = other.m_data;
            m_count = other.m_count;

            if (m_count != nullptr)
            {
                ++(*m_count);
            }

            return *this;
        }
        shared_ptr &operator=(shared_ptr &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            if (m_count != nullptr)
            {
                if (--(*m_count) == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }

            m_data = other.m_data;
            m_count = other.m_count;

            other.m_data = nullptr;
            other.m_count = nullptr;

            return *this;
        }

        ~shared_ptr()
        {
            if (m_count != nullptr)
            {
                if (--(*m_count) == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }
        }

        T &operator*()
        {
            return *m_data;
        }

        T &operator*() const
        {
            return *m_data;
        }

        T *operator->()
        {
            return m_data;
        }

        T *operator->() const
        {
            return m_data;
        }

        T *get()
        {
            return m_data;
        }

        void reset(T *data)
        {
            if (m_count != nullptr)
            {
                if (--(*m_count) == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }

            m_data = data;
            m_count = new size_t(1);
        }

        size_t use_count() const
        {
            return *m_count;
        }

        T *data() { return m_data; }
        size_t *count() { return m_count; }

        T *data() const { return m_data; }
        size_t *count() const { return m_count; }

    public:
        T *m_data;
        size_t *m_count;
    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args &&...args)
    {
        return shared_ptr<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename U>
    shared_ptr<T> static_shared_pointer_cast(const shared_ptr<U> &other)
    {
        shared_ptr<T> res;
        res.reset(static_cast<T *>(other.data()));
        return res;
    }
}