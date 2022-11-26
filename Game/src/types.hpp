#pragma once
#include "engine/brown.hpp"

namespace Events::Player {
    const event_id HEALTH = "Event::Player::HEALTH"_hash;
    namespace Health {
        const param_id HEALTH = "Event::Player::Health::HEALTH"_hash;
    }
}

namespace Events::Entity::Interact {
    const event_id ID = "Event::Entity::Interact::ID"_hash;
    namespace Id {
        const param_id ID = "Event::Entity::Interact::ID::ID"_hash;
    }
}