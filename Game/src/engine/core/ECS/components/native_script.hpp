#pragma once
#include "core/ECS/entity/scriptable_entity.hpp"
#include <functional>

/**
 * @brief Native script component.
 * 
 * 
 * This component is used to attach a native script to an entity.
 * Use <code>bind<T>()</code> to bind a script to an entity.
 */
struct native_script
{
    brown::scriptable_entity *instance = nullptr;

    brown::scriptable_entity *(*instantiate_script)();

    void (*destroy_script)(native_script *);

    /**
     * @brief Bind a script to an entity.
     * 
     * @tparam T The script to bind.
     */
    template <typename T, typename ...Args>
    void bind(Args&& ... args)
    {
        /* instantiate_script = [&]()
        { return static_cast<brown::scriptable_entity*>(new T(args...)); }; */
        instance = new T(std::forward<T>(args)...);
        destroy_script = [](native_script *nsc)
        { delete nsc->instance; nsc->instance = nullptr; };
    }

    bool created = false;
};