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
    inventory(const inventory &other) {
        for(auto &item : other.m_items) {
            m_items.push_back({item.i, item.count});
        }
    }

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
                if (*(item.i) == *i) {
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

                if (item.count == 0) {
                    //m_items.erase(item);
                }
            }
        }
     }

    int items() { return m_items.size(); }

    

    std::vector<inventory_item> get_items() { return m_items; }

private:
    std::vector<inventory_item> m_items;
};