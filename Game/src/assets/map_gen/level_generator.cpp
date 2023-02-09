#include "level_generator.hpp"

int level_generator::neighbour_count(int index) {
    return this->m_floorplan[index-10] + this->m_floorplan[index-1] + this->m_floorplan[index+1] + this->m_floorplan[index+10];
}

bool level_generator::visit(int index ) {
    if (this->m_floorplan[index])
        return false;

    int neighbours = this->neighbour_count(index);

    if (neighbours > 1)
        return false;

    if (m_room_count >= max_rooms)
        return false;

    if (this->rand(this->rng) < 0.5 && index != 45) 
        return false;

    this->m_rooms.push(index);
    this->m_floorplan[index] = 1;
    m_room_count++;

    return true;
}

void level_generator::start() {
    for(int i = 0; i < 100; i++) {
        this->m_floorplan[i] = 0;
    }

    this->placed_special = false;
    this->m_room_count = 0;

    this->m_endrooms = brown::dt::queue<int>();
    this->m_rooms = brown::dt::queue<int>();

    this->visit(45);
}

void level_generator::generate() {
    start();

    while(!this->m_rooms.empty()) {
        int index = this->m_rooms.front();
        this->m_rooms.pop();

        int x = index % 10;
        bool created = false;

        if (x > 1)
            created = created | visit(index - 1);
        if (x < 9)
            created = created | visit(index + 1);
        if (index > 20)
            created = created | visit(index - 10);
        if (index < 70)
            created = created | visit(index + 10);

        if (!created)
            this->m_endrooms.push(index);
    }

    if (this->m_room_count < min_rooms)
        generate();
}