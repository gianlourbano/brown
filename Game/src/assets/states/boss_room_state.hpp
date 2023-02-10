#include "room_state.hpp"

class boss_room_state : public room_state
{
    public:
        boss_room_state() = delete;
        boss_room_state(room_data data) : room_state(data) {}
};