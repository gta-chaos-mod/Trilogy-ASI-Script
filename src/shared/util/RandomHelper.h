#pragma once

#include <random>

class RandomHelper
{
private:
	static std::mt19937 rng;

public:
	static void SetSeed(int seed);
	static std::mt19937 GetRNG();

	static int Random(int min, int max);
	static int Random(int min, int max, int amplify);

	static float Random(float min, float max);
	static float Random(float min, float max, int amplify);
};
