#pragma once
#include "door_controller.hpp"

class boss_door_controller : public door_controller
{
    public:
        boss_door_controller(door_data data): door_controller(data) {};
};