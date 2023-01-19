#pragma once
#include "brown.hpp"
#include "scriptable_AI.hpp"

class auto_attack : public brown::scriptable_entity
{
public:
    

    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
    }

    void on_update()
    {
        
        for (auto &e : m_state->get_entities())
            {
                auto &ts_ = e.get_component<transform>();
                float dist = distance(ts->position, ts_.position);
                if (dist <= 2 && dist > 0 && e.get_id() != this->m_entity.get_id())
                {
                    scriptable_AI *script = dynamic_cast<scriptable_AI *>(e.get_component<native_script>().instance);
                    if (script != nullptr)
                    {
                        script->on_hit();
                    }
                }
            }

            anim->play("attack", [this]()
                       {LOG("attack deleted");this->delete_self(); });
    }

    void on_destroy()
    {
        ts = nullptr;
        anim = nullptr;
    }


private:
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
    friend class player_controller;
};