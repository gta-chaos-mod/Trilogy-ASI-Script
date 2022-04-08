#pragma once

#include <random>

class RandomHelper
{
private:
    static inline std::mt19937 rng;

public:
    static void
    SetSeed (int seed)
    {
        rng.seed (seed);
    }
    static std::mt19937
    GetRNG ()
    {
        return rng;
    }

    static int
    Random (int min, int max)
    {
        return Random (min, max, 1);
    }
    static int
    Random (int min, int max, int amplify)
    {
        std::uniform_int_distribution unif (min, max);
        return unif (rng) * amplify;
    }

    static float
    Random (float min, float max)
    {
        return Random (min, max, 1);
    }
    static float
    Random (float min, float max, int amplify)
    {
        std::uniform_real_distribution<float> unif (min, max);
        return unif (rng) * amplify;
    }
};
