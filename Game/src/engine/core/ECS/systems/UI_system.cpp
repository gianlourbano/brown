#include "UI_system.hpp"
#include "engine/core/ECS/components/transform.hpp"

std::shared_ptr<brown::UI_system> brown::UI_system::register_system(brown::brain *br)
{
    auto sys = br->register_system<brown::UI_system>();
    signature signature;
    signature.set(br->get_component_type<ui>());
    signature.set(br->get_component_type<transform>());
    br->set_system_signature<brown::UI_system>(signature);
    return sys;
}

void brown::UI_system::init()
{
}

void brown::UI_system::draw(WINDOW *win, brown::brain *br) {
    for (auto &entity : m_entities) {
        auto &ui_ = br->get_component<ui>(entity);
        auto &tr = br->get_component<transform>(entity);
        if (ui_.is_visible) {
            mvwprintw(win, tr.position.y, tr.position.x, ui_.text.c_str());
        }
    }
}
