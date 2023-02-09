#pragma once
#include <utility>

namespace brown::mem
{

    /**
     * @brief A unique pointer class.
     *
     * A unique pointer is a wrapper around a pointer that ensures that the pointer is deleted when the unique pointer is destroyed.
     *
     * @tparam T the type of the pointer
     */
    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr() : m_data(nullptr) {}
        explicit unique_ptr(T *data) : m_data(data) {}
        unique_ptr(const unique_ptr &other) = delete;
        unique_ptr(unique_ptr &&other) noexcept = default;

        unique_ptr &operator=(const unique_ptr &other) = delete;
        unique_ptr &operator=(unique_ptr &&other) noexcept = default;

        ~unique_ptr()
        {
            if (m_data != nullptr)
            {

                m_data->~T();
            }
        }

        T &operator*()
        {
            return *m_data;
        }

        T *operator->()
        {
            return m_data;
        }

        T *get()
        {
            return m_data;
        }

        void reset(T *data)
        {
            if (m_data != nullptr)
            {
                delete m_data;
            }

            m_data = data;
        }

    private:
        T *m_data;
    };

    template <typename T, typename... Args>
    unique_ptr<T> make_unique(Args &&...args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

}