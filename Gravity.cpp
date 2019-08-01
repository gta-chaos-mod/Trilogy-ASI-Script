#include "Gravity.h"

Gravity::Gravity(float _gravity, int duration, std::string description)
	: TimedEffect(duration, description, "gravity") {
	gravity = _gravity;
}

void Gravity::Enable() {
	GAME_GRAVITY = gravity;
}

void Gravity::Disable() {
	GAME_GRAVITY = 0.008f;
}

void Gravity::HandleTick() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}