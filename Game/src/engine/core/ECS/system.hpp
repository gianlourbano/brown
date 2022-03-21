#pragma once
#include "core/types.hpp"
#include <set>

namespace brown
{
    class system
    {
    public:
        std::set<entity_id> m_entities;
    };
}