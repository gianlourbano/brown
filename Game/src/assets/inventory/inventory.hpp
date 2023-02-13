#pragma once
#include "item.hpp"
#include "engine/std/list.hpp"
#include "engine/std/vector.hpp"

// struct inventory_item {
//     item *i;
//     int count;

//     inventory_item (item *i, int count) : i(i), count(count) {}
// };

// class inventory {
// public:
//     inventory() {}
//     ~inventory() {}
//     inventory(const inventory &other) {
//         for(auto &item : other.m_items) {
//             m_items.push_back({item.i, item.count});
//         }
//     }

//     bool find_item(item *i) {
//         for (auto &item : m_items) {
//             if (*(item.i) == *i) {
//                 return true;
//             }
//         }
//         return false;
//     }

//     int get_item_count(item *i) {
//         int count = 0;

//         for(auto &item : m_items) {
//             if (*(item.i) == *i) {
//                 count += item.count;
//             }
//         }

//         return count;
//     }

//     void add_item(item *i) {
//         if (find_item(i)) {
//             for (auto &item : m_items) {
//                 if (*(item.i) == *i) {
//                     item.count++;
//                 }
//             }
//         } else {
//             m_items.push_back({i, 1});
//         }
//      }

//     void remove_item(item *i) {
//         if (find_item(i)) {
//             for (auto &item : m_items) {
//                 if (item.i == i) {
//                     item.count--;
//                     return;
//                 }

//                 if (item.count == 0) {
//                     //m_items.erase(item);
//                 }
//             }
//         }
//      }

//     int items() { return m_items.size(); }

//     std::vector<inventory_item> get_items() { return m_items; }

// private:
//     std::vector<inventory_item> m_items;
// };

class inventory
{
private:
    brown::dt::list<item *> m_items;
    unsigned int m_size = 0;

public:
    inventory() {}
    inventory(inventory &other)
    {
        this->m_items = other.m_items;
    }
    ~inventory() {}

    template <typename T, typename... Args>
    void add_item(Args &&...args)
    {
        add_item(new T(std::forward<Args>(args)...));
    }

    void add_item(item *i)
    {
        for (auto &item : m_items)
        {
            if (*item == *i)
            {
                item->add_count(1);
                return;
            }
        }

        m_items.insert_tail(i);
        m_size++;
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