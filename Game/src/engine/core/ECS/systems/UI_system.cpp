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

void brown::UI_system::LOG_COLORS()
{
    for (int i = 0; i < 60; i++)
    {
        short fg, bg;
        pair_content(i, &fg, &bg);
        LOG("Pair number " + std::to_string(i) + " has fg: " + std::to_string(fg) + " and bg: " + std::to_string(bg));
    }
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
            int b = PAIR_NUMBER((mvwinch(win, tr.position.y - ui_.offset.y, tr.position.x - ui_.offset.x) & A_ATTRIBUTES));
            short bg, fg;
            pair_content(b, &fg, &bg);

            m_pairs.insert({bg, TEXT + m_step});

            brown::colors::make_pair(TEXT + m_step, COLOR_WHITE, bg);

            wattron(win, COLOR_PAIR(m_pairs[bg]) | A_BOLD);

            if (ui_.centered)
            {
                int x = tr.position.x + 1 - ui_.text.size() / 2;
                mvwprintw(win, tr.position.y, x - ui_.offset.x, "%s", ui_.text.c_str());
            }
            else
            {
                mvwprintw(win, tr.position.y - ui_.offset.y, tr.position.x - ui_.offset.x, "%s", ui_.text.c_str());
            }

            wattron(win, COLOR_PAIR(m_pairs[bg]) | A_BOLD);
            if(m_step < 70)
                m_step++;
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
