#pragma once

#include <random>

class RandomHelper
{
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
    Random (int min = 0, int max = 1, int amplify = 1)
    {
        if (max < min) max = min;

        std::uniform_int_distribution unif (min, max);
        return unif (rng) * amplify;
    }

    float
    Random (float min = 0.0f, float max = 1.0f, float amplify = 1)
    {
        if (max < min) max = min;

        std::uniform_real_distribution<float> unif (min, max);
        return unif (rng) * amplify;
    }
};
