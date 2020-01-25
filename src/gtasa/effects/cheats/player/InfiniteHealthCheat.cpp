#include "InfiniteHealthCheat.h"

InfiniteHealthCheat::InfiniteHealthCheat()
	: EffectBase("cheat_infinite_health")
{
	AddType("health");
}

void InfiniteHealthCheat::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : { 0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83, 0x6F225A }) {
		HookCall(address, HookedKillPedsInVehicle);
	}

	// TODO: Implement vehicle upside-down check
}

void InfiniteHealthCheat::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
	}

	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (vehicle) {
		vehicle->m_nPhysicalFlags.bInvulnerable = true;
		vehicle->m_nPhysicalFlags.bBulletProof = true;
		vehicle->m_nPhysicalFlags.bCollisionProof = true;
		vehicle->m_nPhysicalFlags.bExplosionProof = true;
		vehicle->m_nPhysicalFlags.bFireProof = true;
		vehicle->m_nPhysicalFlags.bMeeleProof = true;
	}
}

void __fastcall InfiniteHealthCheat::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4) {
	if (ped == FindPlayerPed()) {
		return;
	}

	thisCalc->ComputeWillKillPed(ped, cDamageReponseInfo, a4);
}

void __fastcall InfiniteHealthCheat::HookedKillPedsInVehicle(CVehicle* thisVehicle) {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (vehicle && vehicle == thisVehicle) {
		thisVehicle->m_nStatus = eEntityStatus::STATUS_SIMPLE;
	}
}
