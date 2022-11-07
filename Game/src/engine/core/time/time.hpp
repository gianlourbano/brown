#pragma once
#include <chrono>
#include <random>

extern int FPS;

namespace brown {

    double get_rand_double(double lower_bound, double upper_bound) {
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re;
        return unif(re);
    }

    class Timer {
    public:
        Timer() : m_start(std::chrono::high_resolution_clock::now()) {}
        void start() { m_start = std::chrono::high_resolution_clock::now(); }
        double elapsed() const {
            return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_start).count();
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    };
}