#pragma once

#include <algorithm>
#include <iterator>

namespace brown::dt
{
    template <typename T>
    class node
    {
    public:
        T data;
        node<T> *next;
        node<T> *prev;

        node() : data(), next(nullptr), prev(nullptr) {}
        node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
        node(T &&data) : data(std::move(data)), next(nullptr), prev(nullptr) {}
        node(const node<T> &other) : data(other.data), next(other.next), prev(other.prev) {}
        node(node<T> &&other) noexcept : data(std::move(other.data)), next(other.next), prev(other.prev) {}
        node<T> &operator=(const node<T> &other)
        {
            if (this == &other)
            {
                return *this;
            }
            data = other.data;
            next = other.next;
            prev = other.prev;
            return *this;
        }
        node<T> &operator=(node<T> &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            data = std::move(other.data);
            next = other.next;
            prev = other.prev;
            return *this;
        }
        ~node() {}

        const T &get_data() const
        {
            return data;
        }

        T &get_data()
        {
            return data;
        }
    };

    template <typename T>
    class list
    {

    private:
        node<T> *m_head;
        node<T> *m_tail;
        size_t m_size;

    public:
        list() : m_head(nullptr), m_tail(nullptr), m_size(0) {}
        list(const list<T> &other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {}
        list(list<T> &&other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {}
        list<T> &operator=(const list<T> &other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            return *this;
        }
        list<T> &operator=(list<T> &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            return *this;
        }
        ~list() {}

        void push_back(const T &data)
        {
            node<T> *new_node = new node<T>(data);
            if (m_head == nullptr)
            {
                m_head = new_node;
                m_tail = new_node;
            }
            else
            {
                m_tail->next = new_node;
                new_node->prev = m_tail;
                m_tail = new_node;
            }
            ++m_size;
        }

        void push_back(T &&data)
        {
            node<T> *new_node = new node<T>(std::move(data));
            if (m_head == nullptr)
            {
                m_head = new_node;
                m_tail = new_node;
            }
            else
            {
                m_tail->next = new_node;
                new_node->prev = m_tail;
                m_tail = new_node;
            }
            ++m_size;
        }

        void push_front(const T &data)
        {
            node<T> *new_node = new node<T>(data);
            if (m_head == nullptr)
            {
                m_head = new_node;
                m_tail = new_node;
            }
            else
            {
                m_head->prev = new_node;
                new_node->next = m_head;
                m_head = new_node;
            }
            ++m_size;
        }

        void push_front(T &&data)
        {
            node<T> *new_node = new node<T>(std::move(data));
            if (m_head == nullptr)
            {
                m_head = new_node;
                m_tail = new_node;
            }
            else
            {
                m_head->prev = new_node;
                new_node->next = m_head;
                m_head = new_node;
            }
            ++m_size;
        }

        void pop_back()
        {
            if (m_tail == nullptr)
            {
                return;
            }
            node<T> *temp = m_tail;
            m_tail = m_tail->prev;
            if (m_tail != nullptr)
            {
                m_tail->next = nullptr;
            }
            delete temp;
            --m_size;
        }

        void pop_front()
        {
            if (m_head == nullptr)
            {
                return;
            }
            node<T> *temp = m_head;
            m_head = m_head->next;
            if (m_head != nullptr)
            {
                m_head->prev = nullptr;
            }
            delete temp;
            --m_size;
        }

        void clear()
        {
            while (m_head != nullptr)
            {
                node<T> *temp = m_head;
                m_head = m_head->next;
                delete temp;
            }
            m_tail = nullptr;
            m_size = 0;
        }

        void remove(const T &data)
        {
            node<T> *temp = m_head;
            while (temp != nullptr)
            {
                if (temp->data == data)
                {
                    if (temp->prev != nullptr)
                    {
                        temp->prev->next = temp->next;
                    }
                    else
                    {
                        m_head = temp->next;
                    }
                    if (temp->next != nullptr)
                    {
                        temp->next->prev = temp->prev;
                    }
                    else
                    {
                        m_tail = temp->prev;
                    }
                    delete temp;
                    --m_size;
                    return;
                }
                temp = temp->next;
            }
        }

        void remove(T &&data)
        {
            node<T> *temp = m_head;
            while (temp != nullptr)
            {
                if (temp->data == data)
                {
                    if (temp->prev != nullptr)
                    {
                        temp->prev->next = temp->next;
                    }
                    else
                    {
                        m_head = temp->next;
                    }
                    if (temp->next != nullptr)
                    {
                        temp->next->prev = temp->prev;
                    }
                    else
                    {
                        m_tail = temp->prev;
                    }
                    delete temp;
                    --m_size;
                    return;
                }
                temp = temp->next;
            }
        }

        void remove_if(std::function<bool(const T &)> predicate)
        {
            node<T> *temp = m_head;
            while (temp != nullptr)
            {
                if (predicate(temp->data))
                {
                    if (temp->prev != nullptr)
                    {
                        temp->prev->next = temp->next;
                    }
                    else
                    {
                        m_head = temp->next;
                    }
                    if (temp->next != nullptr)
                    {
                        temp->next->prev = temp->prev;
                    }
                    else
                    {
                        m_tail = temp->prev;
                    }
                    node<T> *temp2 = temp;
                    temp = temp->next;
                    delete temp2;
                    --m_size;
                }
                else
                {
                    temp = temp->next;
                }
            }

        }

        node<T> *begin() const
        {
            return m_head;
        }

        node<T> *end() const
        {
            return nullptr;
        }

        node<T> *rbegin() const
        {
            return m_tail;
        }

        node<T> *rend() const
        {
            return nullptr;
        }

        size_t size() const
        {
            return m_size;
        }

        bool empty() const
        {
            return m_size == 0;
        }


    };
}