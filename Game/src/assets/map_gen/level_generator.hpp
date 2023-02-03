#pragma once
#include <queue>
#include <vector>
#include <random>

class level_generator{
    private:
        std::queue<int> m_endrooms;     // Stack con l'ultima stanza visitata
        std::queue<int> m_rooms;        // Stack con tutte le stanze

        std::vector<int> m_floorplan;   // Vettore con le stanze

        int m_room_count = 0;           

        bool placed_special = false;    
        int min_rooms = 12;             // minimo stanze
        int max_rooms = 20;             // massimo stanze

        std::mt19937 rng;
        std::uniform_real_distribution<double> rand;

    private:
        void pop_endroom();
        void pick_secretroom();

        int neighbour_count(int);

    public:
        level_generator()
        {
            for (int i = 0; i < 100; i++)
            {
                this->m_floorplan.push_back(0);
            }
            rng = std::mt19937(time(NULL));
            rand = std::uniform_real_distribution<double>(0, 1);
        }

        bool visit(int);

        void start();

        void generate();

        std::vector<int> get_floorplan()
        {
            return this->m_floorplan;
        }
};