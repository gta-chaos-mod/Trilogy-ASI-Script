#include "InfiniteHealthEveryoneEffect.h"

InfiniteHealthEveryoneEffect::InfiniteHealthEveryoneEffect()
	: EffectBase("effect_infinite_health_everyone")
{
	AddType("health");
}

void InfiniteHealthEveryoneEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : { 0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83, 0x6F225A }) {
		HookCall(address, HookedKillPedsInVehicle);
	}
}

void InfiniteHealthEveryoneEffect::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
	}

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bInvulnerable = true;
		vehicle->m_nPhysicalFlags.bBulletProof = true;
		vehicle->m_nPhysicalFlags.bCollisionProof = true;
		vehicle->m_nPhysicalFlags.bExplosionProof = true;
		vehicle->m_nPhysicalFlags.bFireProof = true;
		vehicle->m_nPhysicalFlags.bMeeleProof = true;
	}
}

void __fastcall InfiniteHealthEveryoneEffect::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4) {}

void __fastcall InfiniteHealthEveryoneEffect::HookedKillPedsInVehicle(CVehicle* thisVehicle) {
	if (thisVehicle && thisVehicle->m_pDriver) {
		thisVehicle->m_nStatus = eEntityStatus::STATUS_SIMPLE;
	}
}
