#include "ToTheLeftToTheRight.h"

ToTheLeftToTheRight::ToTheLeftToTheRight(int duration, std::string description) : TimedEffect(duration, description) {}

void ToTheLeftToTheRight::HandleTick() {
	if (wait > 0) {
		wait -= (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
		return;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (!vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}

		vehicle->m_vecMoveSpeed.x = Random(-0.25f, 0.25f, 2);
		vehicle->m_vecMoveSpeed.y = Random(-0.25f, 0.25f, 2);
		vehicle->m_vecMoveSpeed.z = Random(-0.05f, 0.05f, 2);
	}

	wait = Random(2000, 5000);
}