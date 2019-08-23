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
	if (player && vehicle && vehicle->IsDriver(player)) {
		vehicle->m_nPhysicalFlags.bInvulnerable = player->m_pVehicle == vehicle;
		vehicle->m_nPhysicalFlags.bExplosionProof = player->m_pVehicle == vehicle;
	}
}
