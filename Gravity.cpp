#include "Gravity.h"

Gravity::Gravity(float _gravity, int duration, std::string description) : TimedEffect(duration, description) {
	gravity = _gravity;
}

void Gravity::Enable() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
	}
	GAME_GRAVITY = gravity;
}

void Gravity::Disable() {
	GAME_GRAVITY = 0.008f;
}