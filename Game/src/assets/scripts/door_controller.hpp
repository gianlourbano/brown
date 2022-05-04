#pragma once
#include "engine/brown.hpp"

class door_controller : public brown::scriptable_entity
{
    void on_create() {
        anim = &get_component<animator_controller>();
    }

    void on_update() {
        if(brown::KEY_PRESSED == 'u')
            anim->play("open");
    }

    private:
        animator_controller* anim = nullptr;
};