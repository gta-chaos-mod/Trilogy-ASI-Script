#include "Gravity.h"

Gravity::Gravity(float _gravity, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "gravity") {
	gravity = _gravity;
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

	GAME_GRAVITY = gravity;
}
