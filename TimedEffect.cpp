#include "TimedEffect.h"

TimedEffect::TimedEffect(int _duration, std::string _description) {
	isInitialized = false;
	remaining = duration = _duration;
	if (!_description.empty()) {
		description = _description;
	}
}

TimedEffect::TimedEffect(int _duration, std::string _description, std::string _type) : TimedEffect::TimedEffect(_duration, _description) {
	type = _type;
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

bool TimedEffect::IsEqualDescription(TimedEffect* otherEffect) {
	return GetDescription() == otherEffect->GetDescription();
}

std::string TimedEffect::GetType() {
	return type;
}

bool TimedEffect::IsEqualType(TimedEffect* otherEffect) {
	return GetType() != "" && otherEffect->GetType() != "" && GetType() == otherEffect->GetType();
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
