#pragma once
#include "item.hpp"
#include <vector>

struct inventory_item {
    item *i;
    int count;

    inventory_item (item *i, int count) : i(i), count(count) {}
};

class inventory {
public:
    inventory() {}
    ~inventory() {}

    bool find_item(item *i) {
        for (auto &item : m_items) {
            if (*(item.i) == *i) {
                return true;
            }
        }
        return false;
    }

    int get_item_count(item *i) {
        int count = 0;

        for(auto &item : m_items) {
            if (*(item.i) == *i) {
                count += item.count;
            }
        }

        return count;
    }

    void add_item(item *i) { 
        if (find_item(i)) {
            for (auto &item : m_items) {
                if (item.i == i) {
                    item.count++;
                }
            }
        } else {
            m_items.push_back({i, 1});
        }
     }

    void remove_item(item *i) { 
        if (find_item(i)) {
            for (auto &item : m_items) {
                if (item.i == i) {
                    item.count--;
                    return;
                }
            }
        }
     }

    

    std::vector<inventory_item> get_items() { return m_items; }

private:
    std::vector<inventory_item> m_items;
};