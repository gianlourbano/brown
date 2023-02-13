#pragma once
#include "engine/brown.hpp"
#include "types.hpp"
#include "assets/inventory/inventory.hpp"
#include "assets/scripts/scriptable_AI.hpp"
#include "assets/scripts/projectile.hpp"

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
    entity_id get_closest_entity();

    void interact();

    void on_hit(int);

    player_controller(player_data data);

    void update_data(player_data data);

    void on_create();

    void on_update();

    void set_health(int h);

    void set_score(int k);

    void set_max_health(int h);

    int get_max_health();

    void shoot(int dir);

    int get_health();

    int get_score();

    player_data get_data();

    void add_item(item *i);

    void remove_item(std::string item_name);

    void LOG_INVENTORY();

    inventory *get_inventory();

protected:
    animator_controller *anim = nullptr;

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