// Copyright (c) 2019 Lordmau5
#include "SmashNBoom.h"

SmashNBoom::SmashNBoom(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {}

void SmashNBoom::Disable() {
	*smashNBoomCheat = false;

	TimedEffect::Disable();
}

void SmashNBoom::HandleTick() {
	*smashNBoomCheat = true;

	CPlayerPed* player = FindPlayerPed();
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		bool proof = (player && player->m_pVehicle == vehicle && player->m_pVehicle->IsDriver(player));
		vehicle->m_nPhysicalFlags.bInvulnerable = proof;
		vehicle->m_nPhysicalFlags.bExplosionProof = proof;
		vehicle->m_nPhysicalFlags.bFireProof = proof;
		vehicle->m_nPhysicalFlags.bCollisionProof = proof;
	}
}
