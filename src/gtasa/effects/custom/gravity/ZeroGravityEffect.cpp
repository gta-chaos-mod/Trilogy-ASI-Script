#include "ZeroGravityEffect.h"

ZeroGravityEffect::ZeroGravityEffect()
	: EffectBase("effect_zero_gravity")
{
	AddType("gravity");
	SetEffectDuration(1000 * 10);
}

void ZeroGravityEffect::Disable() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPhysicalFlags.bApplyGravity = true;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bApplyGravity = true;
	}

	EffectBase::Disable();
}

void ZeroGravityEffect::HandleTick() {
	EffectBase::HandleTick();

	GameUtil::SetVehiclesToRealPhysics();

	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPhysicalFlags.bApplyGravity = false;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bApplyGravity = false;
	}
}
