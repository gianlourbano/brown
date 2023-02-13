#pragma once
#include "assets/inventory/inventory.hpp"
#include "assets/scripts/scriptable_AI.hpp"

struct player_data
{
    int health = 100;
    int max_health = 100;

    int attack_damage = 20;
    int defense = 5;

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
    player_controller(player_data data);

    void interact();
    void on_hit(int);

    entity_id get_closest_entity();

    void on_create();
    void on_update();

    void update_data(player_data data);
    void set_health(int h);
    void set_score(int k);
    void set_max_health(int h);
    void set_defense(int);
    void set_attack(int);

    int get_max_health();
    int get_health();
    int get_score();
    int get_defense();
    int get_attack();

    void shoot(int dir);

    player_data get_data();

    bool add_item(item *i);
    void remove_item(std::string item_name);
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