// Copyright (c) 2019 Lordmau5
#include "CustomGravity.h"

CustomGravity::CustomGravity(float _gravity, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "gravity") {
	gravity = _gravity;
}

void CustomGravity::Disable() {
	GAME_GRAVITY = 0.008f;
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

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}

	GAME_GRAVITY = gravity;

	// Potentially fix bikes disappearing with zero / negative gravity
	injector::WriteMemory(0x871494, gravity == 0.0f ? -0.00000001f : (-gravity / 2), true);
}
