#include "scripts_system.hpp"
#include "state.hpp"
#include "core/ECS/entity/scriptable_entity.hpp"

namespace brown
{
    std::shared_ptr<scripts_system> scripts_system::register_system(brown::brain *br)
    {
        std::shared_ptr<scripts_system> sys = br->register_system<brown::scripts_system>();
        signature signature;
        signature.set(br->get_component_type<native_script>());
        br->set_system_signature<brown::scripts_system>(signature);
        return sys;
    }

    void scripts_system::update(state *st)
    {
        for (auto &e : m_entities)
        {
            auto &script = st->brain.get_component<native_script>(e);

            if (!script.created)
            {
                script.created = true;
                //script.instance = script.instantiate_script();
                script.instance->m_entity = entity{"", e, &(st->brain)};
                script.instance->m_state = st;
                script.instance->on_create();
            }
            script.instance->on_update();
        }
    }

    void scripts_system::on_destroy(state *st)
    {
        for (auto &e : m_entities)
        {
            auto &script = st->brain.get_component<native_script>(e);

            if (script.instance)
            {
                script.instance->on_destroy();
                st->m_controller.empty_to_be_deleted();
            }
        }
    }
}