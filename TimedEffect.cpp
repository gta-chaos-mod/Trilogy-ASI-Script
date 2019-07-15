#include "TimedEffect.h"

TimedEffect::TimedEffect(int _duration, std::string _description) {
	isInitialized = false;
	remaining = duration = _duration;
	if (!_description.empty()) {
		description = _description;
	}
	rng = std::mt19937(std::random_device()());
}

bool TimedEffect::IsRunning() {
	return remaining > 0;
}

int TimedEffect::GetRemaining() {
	return remaining;
}

int TimedEffect::GetDuration() {
	return duration;
}

std::string TimedEffect::GetDescription() {
	return description;
}

void TimedEffect::TickDown() {
	if (!isInitialized) {
		InitializeHooks();

		Enable();
		isInitialized = true;
	}

	if (remaining >= 0) {
		remaining -= CalculateTick();

		HandleTick();

		if (remaining <= 0) {
			Disable();
		}
	}
}

int TimedEffect::Random(int min, int max) {
	return Random(min, max, 1);
}

int TimedEffect::Random(int min, int max, int amplify) {
	std::uniform_int_distribution unif(min, max);
	return unif(rng) * amplify;
}

float TimedEffect::Random(float min, float max) {
	return Random(min, max, 1);
}

float TimedEffect::Random(float min, float max, int amplify) {
	std::uniform_real_distribution<float> unif(min, max);
	return unif(rng) * amplify;
}