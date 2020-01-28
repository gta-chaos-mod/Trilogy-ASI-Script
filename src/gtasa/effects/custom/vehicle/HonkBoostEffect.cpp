#include "HonkBoostEffect.h"

HonkBoostEffect::HonkBoostEffect()
	: EffectBase("effect_honk_boost") {}

void HonkBoostEffect::HandleTick() {
	EffectBase::HandleTick();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_nHornCounter > 0) {
			vehicle->m_vecMoveSpeed.x = (std::min)((std::max)(-10.0f, vehicle->m_vecMoveSpeed.x * 1.025f), 10.0f);
			vehicle->m_vecMoveSpeed.y = (std::min)((std::max)(-10.0f, vehicle->m_vecMoveSpeed.y * 1.025f), 10.0f);
			vehicle->m_vecMoveSpeed.z = (std::min)((std::max)(-10.0f, vehicle->m_vecMoveSpeed.z * 1.025f), 10.0f);
		}
	}
}
