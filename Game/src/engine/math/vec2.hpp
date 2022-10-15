#pragma once
#include <cmath>

/*
    Very simple implementation of a 2D vector,
    with basic operations overloaded.
*/
struct vec2
{
    int x, y;

    vec2() : x(0), y(0){};
    vec2(int c) : x(c), y(c){};
    vec2(int x, int y) : x(x), y(y){};

    vec2 operator+(vec2 const& v) {
        return vec2(this->x+v.x, this->y+v.y);
    }
    vec2 operator+=(vec2 const &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2 operator-(vec2 const &v)
    {
        return vec2(this->x - v.x, this->y - v.y);
    }
    vec2 operator-=(vec2 const &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
};

inline float distance(vec2 v1, vec2 v2) {
    return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}