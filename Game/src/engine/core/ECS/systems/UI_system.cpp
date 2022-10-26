#include "UI_system.hpp"
#include "engine/core/ECS/components/transform.hpp"
#include "engine/graphics/window/window.hpp"
#include "engine/core/color/color.hpp"

#define TEXT 30

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

void brown::UI_system::draw(WINDOW *win, brown::brain *br)
{
    for (auto &entity : m_entities)
    {
        auto &ui_ = br->get_component<ui>(entity);
        auto &tr = br->get_component<transform>(entity);
        if (ui_.is_visible)
        {
            // brown::graphics::mvwprintwcolors(win, tr.position.y, tr.position.x, 18 , ui_.text.c_str());
            int b = PAIR_NUMBER((mvwinch(win, tr.position.y, tr.position.x) & A_ATTRIBUTES));
            short bg, fg;
            pair_content(b, &fg, &bg);
            brown::colors::make_pair(TEXT, COLOR_WHITE, bg);
            wattron(win, COLOR_PAIR(TEXT) | A_BOLD);

            if (ui_.centered)
            {
                int x = tr.position.x + 1 - ui_.text.size() / 2;
                mvwprintw(win, tr.position.y, x - ui_.offset.x, ui_.text.c_str());
            }
            else
            {
                mvwprintw(win, tr.position.y - ui_.offset.y, tr.position.x - ui_.offset.x, ui_.text.c_str());
            }

            wattron(win, COLOR_PAIR(TEXT) | A_BOLD);
        }
    }
}

/*
void brown::UI_system::cleanup(brown::brain *br) {
    for (auto &entity : m_entities) {
        auto &ui_ = br->get_component<ui>(entity);

        ui_.delete_data();
    }
}*/
