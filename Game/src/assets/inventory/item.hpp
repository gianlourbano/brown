#pragma once
#include "brown.hpp"

class player_controller;

struct item : public brown::scriptable_entity
{
    std::string m_name;
    int m_count = 1;

    void add_count(int count)
    {
        m_count += count;
    }

    void remove_count(int count)
    {
        m_count -= count;
    }

    bool operator==(const item &other) const
    {
        return m_name == other.m_name;
    }

    void update_ptr(player_controller* pl) {
        m_player = pl;
    }

protected:
    player_controller* m_player;
};

class consumable : public item
{
public:
    virtual void on_interact(brown::event &e) = 0;
    virtual void on_use() = 0;
};

struct key_item : public item
{
    virtual void on_pickup() = 0;
};

struct artifact : public item
{
    virtual void on_interact(brown::event &e) = 0;
    virtual void on_pickup(player_controller*) = 0;
    virtual void on_remove() = 0;
};