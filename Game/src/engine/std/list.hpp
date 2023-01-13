#pragma once
#include <utility>
#include <iterator>
#include <algorithm>

template <typename T>
class list_node
{
public:
    list_node() {}

    list_node(T &data, list_node<T> *prev)
    {
        m_data = data;
        m_prev = prev;
    }

    list_node(T &&data, list_node<T> *prev)
    {
        m_data = std::move(data);
        m_prev = prev;
    }

    template<typename ...Args>
    list_node(list_node<T> prev, Args... args) {
        m_data = std::forward<T>(args...);
        m_prev = prev;
    }

    list_node<T> *add_node(list_node<T> *next)
    {
        m_next = next;
        return m_next;
    }

    list_node<T> *add_node(T &data)
    {
        m_next = new list_node<T>(data, this);
        return m_next;
    }

    T get_data() {
        return m_data;
    }

public:
    T m_data;
    list_node<T> *m_next = nullptr;
    list_node<T> *m_prev = nullptr;

    friend class Iterator;
};

template <typename T>
class list
{

public:
    void insert(T &data)
    {
        if (root == nullptr)
            root = new list_node<T>(data, nullptr);
        else
        {
            list_node<T> *temp = root;
            root = new list_node<T>(data, nullptr);
            root->m_next = temp;
        }
    }

    void insert(T&& data) {
        if (root == nullptr)
            root = new list_node<T>(data, nullptr);
        else
        {
            list_node<T> *temp = root;
            root = new list_node<T>(data, nullptr);
            root->m_next = temp;
        }
    }

    template<typename ...Args>
    void insert(Args... args) {
        if (root == nullptr)
            root = new list_node<T>(nullptr, std::forward<T>(args)...);
        else
        {
            list_node<T> *temp = root;
            root = new list_node<T>(nullptr, std::forward<T>(args)...);
            root->m_next = temp;
        }
    }

    

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = list_node<T>;
        using pointer = value_type *;
        using reference = value_type &;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        Iterator &operator++()
        {
            m_ptr = m_ptr->m_next;
            return *this;
        }

        // Postfix increment
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    Iterator begin()
    {
        return Iterator(root);
    }

    Iterator end()
    {
        list_node<T> *iter = new list_node<T>();
        iter = this->root;
        while (iter->m_next != nullptr)
        {
            iter = iter->m_next;
        }
        return Iterator(iter);
    }

    

private:
    list_node<T> *root;

    friend class list_node<T>;
};
