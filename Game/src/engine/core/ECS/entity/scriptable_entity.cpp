#include "scriptable_entity.hpp"
#include "state.hpp"

namespace brown {
    void scriptable_entity::delete_self() {
        m_state->delete_entity(m_entity.get_id());
    }
}