#include "RandomHelper.h"

std::mt19937 RandomHelper::rng;

void RandomHelper::SetSeed(int seed) {
	rng.seed(seed);
}

int RandomHelper::Random(int min, int max) {
	return Random(min, max, 1);
}

int RandomHelper::Random(int min, int max, int amplify) {
	std::uniform_int_distribution unif(min, max);
	return unif(rng) * amplify;
}

float RandomHelper::Random(float min, float max) {
	return Random(min, max, 1);
}

float RandomHelper::Random(float min, float max, int amplify) {
	std::uniform_real_distribution<float> unif(min, max);
	return unif(rng) * amplify;
}