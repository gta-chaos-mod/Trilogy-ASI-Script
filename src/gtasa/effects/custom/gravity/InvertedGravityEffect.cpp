#include "InvertedGravityEffect.h"

InvertedGravityEffect::InvertedGravityEffect()
	: EffectBase("effect_inverted_gravity")
{
	AddType("gravity");
	SetEffectDuration(1000 * 10);
}

void InvertedGravityEffect::Disable() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPhysicalFlags.bApplyGravity = true;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bApplyGravity = true;
	}

	EffectBase::Disable();
}

void InvertedGravityEffect::HandleTick() {
	EffectBase::HandleTick();

	GameUtil::SetVehiclesToRealPhysics();

	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPhysicalFlags.bApplyGravity = false;

		ped->m_vecMoveSpeed.z = min(ped->m_vecMoveSpeed.z + 0.001f, 1.0f);
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bApplyGravity = false;

		vehicle->m_vecMoveSpeed.z = min(vehicle->m_vecMoveSpeed.z + 0.001f, 1.0f);
	}
}
