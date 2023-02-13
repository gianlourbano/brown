#include "player_controller.hpp"

entity_id player_controller::get_closest_entity()
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

void player_controller::interact()
{
    brown::event e(Events::Entity::Interact::ID);
    e.set_param<entity_id>(Events::Entity::Interact::ID, get_closest_entity());
    m_state->send_event(e);
}

void player_controller::on_hit(int damage)
{
    if (m_damage_timer.elapsed() >= 1)
    {
        set_health(--m_data.health);
        set_health(m_data.health - damage);
        m_damage_timer.start();
    }
}

player_controller::player_controller(player_data data)
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

void player_controller::update_data(player_data data)
{
    m_data = data;
    set_health(m_data.health);
    set_score(m_data.score);

    for (auto item : m_data.player_inventory->get_items())
    {
        item->update_ptr(this);
    }
}

void player_controller::on_create()
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

void player_controller::on_update()
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

    if (m_proj_lifespan == 0)
        can_shoot = true;

    if (m_proj_lifespan != 0)
        m_proj_lifespan--;
}

void player_controller::set_health(int h)
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

void player_controller::set_score(int k)
{
    m_data.score = k;
    brown::event e(Events::Player::DATA);
    e.set_param(Events::Player::Data::DATA, m_data);
    m_state->send_event(e);
}

void player_controller::set_max_health(int h)
{
    if (h < m_data.health)
        set_health(h);

    m_data.max_health = h;
    brown::event e(Events::Player::DATA);
    e.set_param(Events::Player::Data::DATA, m_data);
    m_state->send_event(e);
}

int player_controller::get_max_health()
{
    return m_data.max_health;
}

int player_controller::get_health()
{
    return m_data.health;
}

int player_controller::get_score()
{
    return m_data.score;
}

player_data player_controller::get_data()
{
    return m_data;
}

void player_controller::add_item(item *i)
{
    artifact *a = dynamic_cast<artifact *>(i);
    if (a != nullptr)
        a->on_pickup(this);
    m_data.player_inventory->add_item(i);

    m_state->send_event(Events::Player::Inventory::ADD);
}

void player_controller::remove_item(std::string item_name)
{
    m_data.player_inventory->remove_item(item_name);

    m_state->send_event(Events::Player::Inventory::ADD);
}

void player_controller::LOG_INVENTORY()
{
    for (auto i : m_data.player_inventory->get_items())
        LOG("Item: " + i->m_name + "x" + std::to_string(i->m_count));
}

inventory *player_controller::get_inventory()
{
    return m_data.player_inventory;
}

void player_controller::shoot(int dir)
{
    if (can_shoot)
    {
        brown::entity proj = m_state->create_entity();
        proj.add_component<transform>({ts->position, dir});
        proj.add_component<sprite>({{2, 2}, "sprite2"});
        proj.add_component<animator_controller>({}).add_anim("explode", proj_anim);
        proj.add_component<native_script>({}).bind<projectile>(m_entity.get_id(), this->m_data.attack_damage);

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
}