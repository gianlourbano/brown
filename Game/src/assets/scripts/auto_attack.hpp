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
        tot = 10;
    }

    void on_update()
    {
        if(tot==10){
        for (auto &e : m_state->get_entities())
            {
                if (m_creator_id != e.get_id()&& e.get_id() != this->m_entity.get_id())
                {
                    LOG(e.name);
                    auto &ts_ = e.get_component<transform>();
                    LOG(&ts);
                    float dist = distance(ts->position, ts_.position);
                    if (dist <= 4 && dist > 0)
                    {
                        
                        scriptable_AI *script = dynamic_cast<scriptable_AI *>(e.get_component<native_script>().instance);
                        
                        if (script != nullptr)
                        {
                            script->on_hit();
                        }
                    }
                }
            }
        }
            anim->play("attack", [this]()
                       {LOG("attack deleted");this->delete_self(); });
            
            if(tot==0){
                this->delete_self();
            }
            tot--;
    }

    void on_destroy()
    {
        ts = nullptr;
        anim = nullptr;
    }

    
private:
    int tot;
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
    entity_id m_creator_id;
    friend class player_controller;
};