#include "TimedEffect.h"

TimedEffect::TimedEffect(int _duration, std::string _description) {
	isInitialized = false;
	remaining = duration = _duration;
	if (!_description.empty()) {
		description = _description;
	}
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

	if (remaining > 0) {
		remaining -= (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);

		HandleTick();

		if (remaining < 0) {
			Disable();
		}
	}
}