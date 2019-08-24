// Copyright (c) 2019 Lordmau5
#include "SmashNBoom.h"

SmashNBoom::SmashNBoom(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void SmashNBoom::Disable() {
	*smashNBoomCheat = false;

	TimedEffect::Disable();
}

void SmashNBoom::HandleTick() {
	*smashNBoomCheat = true;

	CPlayerPed* player = FindPlayerPed();
	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (player && player->m_pVehicle) {
		bool proof = player->m_pVehicle == vehicle && player->m_pVehicle->IsDriver(player);
		player->m_pVehicle->m_nPhysicalFlags.bInvulnerable = proof;
		player->m_pVehicle->m_nPhysicalFlags.bExplosionProof = proof;
	}
}
