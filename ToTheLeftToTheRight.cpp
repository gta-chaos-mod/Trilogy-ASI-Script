#include "ToTheLeftToTheRight.h"

ToTheLeftToTheRight::ToTheLeftToTheRight(int duration, std::string description) : TimedEffect(duration, description) {}

void ToTheLeftToTheRight::HandleTick() {
	if (wait > 0) {
		wait -= (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
		return;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		CCarCtrl::SwitchVehicleToRealPhysics(vehicle);

		vehicle->m_vecMoveSpeed.x = RandomEffect();
		vehicle->m_vecMoveSpeed.y = RandomEffect();
		vehicle->m_vecMoveSpeed.z = RandomEffect();
	}

	std::default_random_engine re;
	std::uniform_int_distribution unif_i(2000, 5000);
	wait = unif_i(re);
}

float ToTheLeftToTheRight::RandomEffect() {
	std::default_random_engine re;

	std::uniform_real_distribution<float> unif(-0.25f, 0.25f);
	float randomEffect = unif(re) * 2.0f;

	return randomEffect;
}