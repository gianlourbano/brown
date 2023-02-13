#include "math.hpp"

int random_int(int min, int max)
{
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do
    {
        x = rand();
    } while (x >= RAND_MAX - remainder);

    return min + x % n;
}