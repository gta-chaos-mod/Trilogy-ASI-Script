// Copyright (c) 2019 Lordmau5
#include "InfiniteHealth.h"

bool InfiniteHealth::onlyPlayer = false;

InfiniteHealth::InfiniteHealth(bool _onlyPlayer, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "health") {
	onlyPlayer = _onlyPlayer;
}

void InfiniteHealth::InitializeHooks() {
	HookCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : { 0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83, 0x6F225A }) {
		HookCall(address, HookedKillPedsInVehicle);
	}
}

void InfiniteHealth::Disable() {
	TimedEffect::Disable();
}

void InfiniteHealth::HandleTick() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
	}

	if (onlyPlayer) {
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
	else {
		for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
			vehicle->m_nPhysicalFlags.bInvulnerable = true;
			vehicle->m_nPhysicalFlags.bBulletProof = true;
			vehicle->m_nPhysicalFlags.bCollisionProof = true;
			vehicle->m_nPhysicalFlags.bExplosionProof = true;
			vehicle->m_nPhysicalFlags.bFireProof = true;
			vehicle->m_nPhysicalFlags.bMeeleProof = true;
		}
	}
}

void __fastcall InfiniteHealth::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4) {
	if (onlyPlayer && ped == FindPlayerPed() || !onlyPlayer) {
		return;
	}

	thisCalc->ComputeWillKillPed(ped, cDamageReponseInfo, a4);
}

void __fastcall InfiniteHealth::HookedKillPedsInVehicle(CVehicle* thisVehicle) {
	thisVehicle->m_nStatus = eEntityStatus::STATUS_SIMPLE;
}
