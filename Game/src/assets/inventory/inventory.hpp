#pragma once
#include "item.hpp"
#include "engine/std/list.hpp"
#include "engine/std/vector.hpp"

class inventory
{
private:
    brown::dt::list<item *> m_items;
    unsigned int m_size = 0;

    int max_size = 10;

public:
    inventory() {}
    inventory(inventory &other)
    {
        this->m_items = other.m_items;
    }
    ~inventory() {}

    

    bool add_item(item *i)
    {
        if(m_size >= max_size) {
            return false;
        }
        for (auto &item : m_items)
        {
            if (*item == *i)
            {
                item->add_count(1);
                return true;
            }
        }

        m_items.insert_tail(i);
        m_size++;
        return true;
    }

    template <typename T, typename... Args>
    bool add_item(Args &&...args)
    {
        return add_item(new T(std::forward<Args>(args)...));
    }

    int get_item_count(item *i)
    {
        int count = 0;

        for (auto &item : m_items)
        {
            if (*item == *i)
            {
                count += item->m_count;
            }
        }

        return count;
    }

    void remove_item(std::string name)
    {
        for (auto &item : m_items)
        {
            if (item->m_name == name)
            {
                item->remove_count(1);

                if (item->m_count == 0)
                {
                    m_items.remove_data(item);
                    m_size--;
                }
            }
        }
    }

    brown::dt::list<item *> get_items()
    {
        return m_items;
    }

    brown::dt::vector<item*> get_items_vector() {
        brown::dt::vector<item*> items;
        for(auto &item : m_items) {
            items.push_back(item);
        }
        return items;
    }

    unsigned int size()
    {
        return m_size;
    }

    item* operator[](int index) {
        return m_items[index];
    }
};