#pragma once
#include "../types.hpp"
#include <set>

namespace brown
{
    class system
    {
    public:
        std::set<entity_id> m_entities;
    };
}