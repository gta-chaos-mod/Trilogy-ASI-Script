#include "RainbowCars.h"

RainbowCars::RainbowCars(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void RainbowCars::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPrimaryColor = ++vehicle->m_nPrimaryColor % 127;
		vehicle->m_nSecondaryColor = vehicle->m_nPrimaryColor + 1 % 127;
		vehicle->m_nTertiaryColor = vehicle->m_nPrimaryColor + 2 % 127;
		vehicle->m_nQuaternaryColor = vehicle->m_nPrimaryColor + 3 % 127;
	}

	wait = 50;
}
