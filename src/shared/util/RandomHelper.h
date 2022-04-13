#pragma once

#include <random>

class RandomHelper
{
private:
    std::mt19937 rng;

public:
    void
    SetSeed (int seed)
    {
        rng.seed (seed);
    }

    std::mt19937
    GetRNG ()
    {
        return rng;
    }

    int
    Random (int min, int max, int amplify = 1)
    {
        std::uniform_int_distribution unif (min, max);
        return unif (rng) * amplify;
    }

    float
    Random (float min, float max, float amplify = 1)
    {
        std::uniform_real_distribution<float> unif (min, max);
        return unif (rng) * amplify;
    }
};
