#pragma once
#include "engine/brown.hpp"

namespace Events::Player {
    const event_id HEALTH = "Event::Player::HEALTH"_hash;
}

namespace Events::Player::Health {
    const param_id HEALTH = "Event::Player::Health::HEALTH"_hash;
}
