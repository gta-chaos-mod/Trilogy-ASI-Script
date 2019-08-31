// Copyright (c) 2019 Lordmau5
#include "LockPlayerInsideVehicle.h"

LockPlayerInsideVehicle::LockPlayerInsideVehicle(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void LockPlayerInsideVehicle::Enable() {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (!vehicle) {
		Disable();
		return;
	}
	vehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED_PLAYER_INSIDE;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_nPedFlags.CantBeKnockedOffBike = 1;
	}
}

void LockPlayerInsideVehicle::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_nPedFlags.CantBeKnockedOffBike = 0;
	}

	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (vehicle) {
		vehicle->m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
	}

	TimedEffect::Disable();
}

void LockPlayerInsideVehicle::HandleTick() {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (!vehicle) {
		Disable();
	}
}
