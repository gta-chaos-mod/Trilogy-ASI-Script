// Copyright (c) 2019 Lordmau5
#include "ToTheLeftToTheRight.h"

ToTheLeftToTheRight::ToTheLeftToTheRight(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void ToTheLeftToTheRight::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	GenericUtil::SetVehiclesRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		int amplify = 2;
		if (RandomHelper::Random(0, 9) == 0) {
			amplify = 4;
		}

		vehicle->m_vecMoveSpeed.x += RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.y += RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.z += RandomHelper::Random(-0.05f, 0.05f, amplify);
	}

	wait = Random(5000, 10000);
}
