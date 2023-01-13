#include "scriptable_entity.hpp"
#include "state.hpp"
#include <vector>

namespace brown
{
    void scriptable_entity::delete_self()
    {
        m_state->delete_entity(m_entity.get_id());
    }

    bool scriptable_entity::is_player_in_range(double range)
    {
        return distance(m_state->find_entity("player").get_component<transform>().position, m_entity.get_component<transform>().position) < range;
    }
}