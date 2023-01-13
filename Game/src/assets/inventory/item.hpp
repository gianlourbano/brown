#pragma once
#include "brown.hpp"

class item : public brown::scriptable_entity
{
    public:
        std::string name;

    friend bool operator==(const item &lhs, const item &rhs)
    {
        return lhs.name == rhs.name;
    }
};

class consumable : public item
{
    virtual void on_interact(brown::event &e) = 0;
    virtual void on_use() = 0;
};

class key_item : public item
{
};