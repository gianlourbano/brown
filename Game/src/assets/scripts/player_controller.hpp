#pragma once
#include "engine/brown.hpp"
#include "assets/scripts/projectile.hpp"
#include "assets/scripts/auto_attack.hpp"
#include "types.hpp"
#include "assets/inventory/inventory.hpp"
#include "assets/scripts/scriptable_AI.hpp"

struct player_data
{
    int health = 100;
    int max_health = 100;

    int attack_damage = 10;
    int defense = 4;

    int score = 0;

    inventory *player_inventory = nullptr;

    player_data() {}
    player_data(inventory *inv)
    {
        player_inventory = inv;
    }
};

class player_controller : public scriptable_AI
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
        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x' || chars[dir - 1] == 'a';
    }

    entity_id get_closest_entity()
    {
        entity_id closest = 0;
        int closest_dist = 1000;
        for (auto &e : m_state->get_entities())
        {
            if (e.get_id() != m_entity.get_id())
            {
                auto &ts = e.get_component<transform>();
                int dist = std::abs(ts.position.x - this->ts->position.x) + std::abs(ts.position.y - this->ts->position.y);
                if (dist < closest_dist)
                {
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

    void on_hit()
    {
        if (m_damage_timer.elapsed() >= 1)
        {
            set_health(--m_data.health);
            m_damage_timer.start();
        }
    }

    player_controller(player_data data)
    {
        m_data = data;

        if (m_data.player_inventory == nullptr)
        {
            m_data.player_inventory = new inventory();
        }

        for (auto item : m_data.player_inventory->get_items())
        {
            item->update_ptr(this);
        }
    }

    void update_data(player_data data)
    {
        m_data = data;
        set_health(m_data.health);
        set_score(m_data.score);

        for (auto item : m_data.player_inventory->get_items())
        {
            item->update_ptr(this);
        }
    }

    void on_create()
    {
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        attack_cooldown.start();
        proj_anim = {
            "animated1",
            2,
            3,
            5,
            false,
            true};
        attack_anim = {
            "animated2",
            3,
            3,
            5,
            false,
            true};

        set_health(m_data.health);
        set_score(m_data.score);
    }

    void on_update()
    {
        if (m_data.health <= 0)
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

        else if (brown::KEY_PRESSED == 'e')
            interact();

        else if (brown::KEY_PRESSED == 't')
        {
            shoot(ts->direction);
        }

        if (brown::KEY_PRESSED == 'i')
        {
            LOG_INVENTORY();
        }

        if (m_proj_lifespan == 0)
            can_shoot = true;

        if (m_proj_lifespan != 0)
            m_proj_lifespan--;
        force = forces[ts->direction - 1];
    }

    void set_health(int h)
    {
        if (h >= m_data.max_health)
            m_data.health = m_data.max_health;
        else
        {
            m_data.health = h;
        }
        brown::event e(Events::Player::DATA);
        e.set_param(Events::Player::Data::DATA, m_data);
        m_state->send_event(e);
    }

    void set_score(int k)
    {
        m_data.score = k;
        brown::event e(Events::Player::DATA);
        e.set_param(Events::Player::Data::DATA, m_data);
        m_state->send_event(e);
    }

    void set_max_health(int h) {
        if (h < m_data.health)
            set_health(h);

        m_data.max_health = h;
        brown::event e(Events::Player::DATA);
        e.set_param(Events::Player::Data::DATA, m_data);
        m_state->send_event(e);
    }

    int get_max_health() {
        return m_data.max_health;
    }

    void shoot(int dir)
    {

        if (can_shoot && !melee)
        {
            brown::entity proj = m_state->create_entity();
            proj.add_component<transform>({ts->position, dir});
            proj.add_component<sprite>({{2, 2}, "sprite2"});
            proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
            proj.add_component<native_script>({}).bind<projectile>(m_entity.get_id());

            can_shoot = false;

            int lifetime = 10;

            switch (dir)
            {
            case 1:
            case 3:
                lifetime /= 2;
                break;
            }
            m_proj_lifespan = lifetime + proj_anim.clips * proj_anim.time_step;
        }
        else if (can_shoot && melee && attack_cooldown.elapsed() >= 0.75)
        {
            brown::entity attack = m_state->create_entity();
            attack.add_component<transform>({ts->position});
            attack.add_component<sprite>({{0, 0}, "sprite2"});
            attack.add_component<animator_controller>({}).add_anim("attack", attack_anim);
            attack.add_component<native_script>({}).bind<auto_attack>();
            attack_cooldown.start();
        }
    }

    int get_health()
    {
        return m_data.health;
    }

    int get_score()
    {
        return m_data.score;
    }

    player_data get_data()
    {
        return m_data;
    }

    void add_item(item *i)
    {
        artifact *a = dynamic_cast<artifact *>(i);
        if (a != nullptr)
            a->on_pickup(this);
        m_data.player_inventory->add_item(i);

        m_state->send_event(Events::Player::Inventory::ADD);
    }

    void remove_item(std::string item_name)
    {
        m_data.player_inventory->remove_item(item_name);

        m_state->send_event(Events::Player::Inventory::ADD);
    }

    void LOG_INVENTORY()
    {
        for (auto i : m_data.player_inventory->get_items())
            LOG("Item: " + i->m_name + "x" + std::to_string(i->m_count));
    }

    inventory *get_inventory()
    {
        return m_data.player_inventory;
    }

protected:
    transform *ts = nullptr;
    animator_controller *anim = nullptr;

    vec2 force;
    animation proj_anim;
    animation attack_anim;

    bool can_shoot = true;
    bool melee = false;
    int m_proj_lifespan = 0;

    brown::Timer m_cooldown;
    brown::Timer attack_cooldown;
    brown::Timer m_damage_timer;

    player_data m_data;
};