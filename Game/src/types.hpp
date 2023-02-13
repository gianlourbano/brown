#pragma once
#include "engine/brown.hpp"

namespace Events::Player {
    const event_id DATA = "Event::Player::DATA"_hash;
    namespace Data {
        const param_id DATA = "Event::Player::Data::DATA"_hash;
    }
}

namespace Events::Entity::Interact {
    const event_id ID = "Event::Entity::Interact::ID"_hash;
    namespace Id {
        const param_id ID = "Event::Entity::Interact::ID::ID"_hash;
    }
}

namespace Events::Player::Inventory {
    const event_id ADD = "Event::Player::Inventory::ADD"_hash;
    namespace Add {
        const param_id ITEM = "Event::Player::Inventory::Add::ITEM"_hash;
    }
    const event_id REMOVE = "Event::Player::Inventory::REMOVE"_hash;
    namespace Remove {
        const param_id ITEM = "Event::Player::Inventory::Remove::ITEM"_hash;
    }
}

namespace Events::Room {
    const event_id Key_picked_up = "Events::Room::Key_picked_up"_hash;
    const event_id Enemy_killed = "Events::Room::Enemy_killed"_hash;
    const event_id World_cleared = "Events::Room::World_cleared"_hash;
}