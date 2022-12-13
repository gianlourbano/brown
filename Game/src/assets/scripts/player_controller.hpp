#pragma once
#include "engine/brown.hpp"
#include "assets/scripts/projectile.hpp"
#include "types.hpp"

class player_controller : public brown::scriptable_entity
{
public:
    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 2) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 2, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        // return !(chars[dir - 1] == ' ' || (chars[dir - 1] <= 'z' && chars[dir - 1] >= 'a'));
        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }

    entity_id get_closest_entity() {
        entity_id closest = 0;
        int closest_dist = 1000;
        for (auto &e : m_state->get_entities()) {
            if (e.get_id() != m_entity.get_id()) {
                auto &ts = e.get_component<transform>();
                int dist = std::abs(ts.position.x - this->ts->position.x) + std::abs(ts.position.y - this->ts->position.y);
                if (dist < closest_dist) {
                    closest_dist = dist;
                    closest = e.get_id();
                }
            }
        }
        return closest;
    }

    void interact()
    {
        brown::event e(Events::Entity::Interact::ID);
        e.set_param<entity_id>(Events::Entity::Interact::ID, get_closest_entity());
        m_state->send_event(e);
    }

    void on_create()
    {
        health = 10;
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        proj_anim = {
            "animated1",
            2,
            5,
            5,
            false,
            true};
    }

    void on_update()
    {
        if (health <= 0)
        {
            m_state->send_event(Events::Window::QUIT);
            return;
        }

        if (brown::KEY_PRESSED == 'a')
        {
            ts->direction = 4;
            if (!check_collision(4))
                ts->position.x--;
        }
        else if (brown::KEY_PRESSED == 'd')
        {
            ts->direction = 2;
            if (!check_collision(2))
                ts->position.x++;
        }

        if (brown::KEY_PRESSED == 'w')
        {
            ts->direction = 1;
            if (!check_collision(1))
                ts->position.y--;
        }
        else if (brown::KEY_PRESSED == 's')
        {
            ts->direction = 3;
            if (!check_collision(3))
                ts->position.y++;
        }

        if (brown::KEY_PRESSED == 'o')
        {
            set_health(--health);
        }

        else if (brown::KEY_PRESSED == 'e')
            interact();

        else if (brown::KEY_PRESSED == 't')
        {
            create_proj(ts->direction);
        }
    }

    void set_health(int h)
    {
        health = h;
        brown::event e(Events::Player::HEALTH);
        e.set_param(Events::Player::Health::HEALTH, health);
        m_state->send_event(e);
    }

    void create_proj(int dir)
    {
        brown::entity proj = m_state->create_entity();
        proj.add_component<transform>({ts->position, dir});
        proj.add_component<sprite>({{2, 2}, "sprite2"});
        proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
        proj.add_component<native_script>({}).bind<projectile>();
    }
    
    int health;
protected:
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
    
    animation proj_anim;

    friend class healtbar_controller;
};
