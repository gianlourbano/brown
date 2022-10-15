#pragma once
#include "core/ECS/entity/scriptable_entity.hpp"

/**
 * @brief Native script component.
 * 
 * This component is used to attach a native script to an entity.
 */
struct native_script
{
    brown::scriptable_entity *instance = nullptr;

    brown::scriptable_entity *(*instantiate_script)();
    void (*destroy_script)(native_script *);

    template <typename T>
    void bind()
    {
        instantiate_script = []()
        { return static_cast<brown::scriptable_entity*>(new T()); };
        destroy_script = [](native_script *nsc)
        { delete nsc->instance; nsc->instance = nullptr; };
    }
};