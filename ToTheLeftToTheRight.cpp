#include "ToTheLeftToTheRight.h"

ToTheLeftToTheRight::ToTheLeftToTheRight(int duration, std::string description)
	: TimedEffect(duration, description) {}

void ToTheLeftToTheRight::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}

		int amplify = 2;
		if (RandomHelper::Random(0, 9) == 0) {
			amplify = 4;
		}

		vehicle->m_vecMoveSpeed.x = RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.y = RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.z = RandomHelper::Random(-0.05f, 0.05f, amplify);
	}

	wait = Random(2000, 5000);
}