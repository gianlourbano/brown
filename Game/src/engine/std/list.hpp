#pragma once

#include <algorithm>
#include <iterator>

namespace brown::dt
{
    template <typename T>
    struct node
    {
        T data;
        node<T> *next = nullptr;
        node<T> *prev = nullptr;
    };

    template <typename T>
    class list
    {
    private:
        node<T> *m_head = nullptr;

    public:
        list() {}
        list(list<T> &other)
        {
            m_head = other.m_head;
        }

        T &operator[](int index)
        {
            node<T> *current = m_head;
            int i = 0;
            while (current != nullptr)
            {
                if (i == index)
                {
                    return current->data;
                }
                current = current->next;
                i++;
            }
        }

        void insert_head(T data)
        {
            node<T> *new_node = new node<T>();
            new_node->data = data;

            if (m_head == nullptr)
            {
                m_head = new_node;
            }
            else
            {
                new_node->next = m_head;
                m_head->prev = new_node;
                m_head = new_node;
            }
        }

        void insert_tail(T data)
        {
            node<T> *new_node = new node<T>();
            new_node->data = data;

            if (m_head == nullptr)
            {
                m_head = new_node;
            }
            else
            {
                node<T> *current = m_head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = new_node;
                new_node->prev = current;
            }
        }

        void remove_data(T data)
        {
            node<T> *current = m_head;
            while (current != nullptr)
            {
                if (current->data == data)
                {
                    if (current->prev != nullptr)
                    {
                        current->prev->next = current->next;
                    }
                    else
                    {
                        m_head = current->next;
                    }
                    if (current->next != nullptr)
                    {
                        current->next->prev = current->prev;
                    }
                    if(current != nullptr)
                        current->~node();
                    return;
                }
                current = current->next;
            }
        }

        class iterator {
        private:
            node<T> *m_current = nullptr;
        public:
            iterator(node<T> *current) : m_current(current) {}
            iterator& operator++() {
                m_current = m_current->next;
                return *this;
            }
            iterator& operator--() {
                m_current = m_current->prev;
                return *this;
            }
            bool operator==(const iterator& other) const {
                return m_current == other.m_current;
            }
            bool operator!=(const iterator& other) const {
                return m_current != other.m_current;
            }
            T& operator*() {
                return m_current->data;
            }
        };

        iterator begin() {
            return iterator(m_head);
        }

        iterator end() {
            return iterator(nullptr);
        }
    };
}