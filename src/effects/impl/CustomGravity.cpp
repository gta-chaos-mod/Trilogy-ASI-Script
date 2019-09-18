// Copyright (c) 2019 Lordmau5
#include "CustomGravity.h"

CustomGravity::CustomGravity(float _gravity, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "gravity") {
	gravity = _gravity;
}

void CustomGravity::Disable() {
	injector::WriteMemory(0x863984, 0.008f, true);
	injector::WriteMemory(0x871494, (-0.008f / 2), true);

	TimedEffect::Disable();
}

int CustomGravity::GetRemaining() {
	return effectRemaining >= 0 ? effectRemaining : remaining;
}

int CustomGravity::GetDuration() {
	return rapidFire ? duration : effectDuration;
}

TimedEffect* CustomGravity::SetRapidFire(bool is_rapid_fire) {
	if (is_rapid_fire) {
		duration = min(duration, effectDuration);
		effectRemaining = duration;
	}

	return TimedEffect::SetRapidFire(is_rapid_fire);
}

void CustomGravity::HandleTick() {
	effectRemaining -= CalculateTick();
	if (effectRemaining <= 0) {
		Disable();
		return;
	}

	GenericUtil::SetVehiclesRealPhysics();

	injector::WriteMemory(0x863984, gravity, true);

	// Potentially fix bikes disappearing with zero / negative gravity
	injector::WriteMemory(0x871494, gravity == 0.0f ? -0.00000001f : (-gravity / 2), true);
}
