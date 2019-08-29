// Copyright (c) 2019 Lordmau5
#include "CustomGravity.h"

CustomGravity::CustomGravity(float _gravity, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "gravity") {
	duration = effectRemaining;
	gravity = _gravity;
}

void CustomGravity::Disable() {
	GAME_GRAVITY = 0.008f;

	TimedEffect::Disable();
}

int CustomGravity::GetRemaining() {
	return effectRemaining >= 0 ? effectRemaining : remaining;
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
}
