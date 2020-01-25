#include "LockPlayerInsideVehicleEffect.h"

LockPlayerInsideVehicleEffect::LockPlayerInsideVehicleEffect()
	: EffectBase("effect_lock_player_inside_vehicle")
{
	SetCanTickWhenDisabled();
}

bool LockPlayerInsideVehicleEffect::CanActivate() {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);

	return vehicle != nullptr;
}

void LockPlayerInsideVehicleEffect::Enable() {
	EffectBase::Enable();

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

void LockPlayerInsideVehicleEffect::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_nPedFlags.CantBeKnockedOffBike = 0;
	}

	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (vehicle) {
		vehicle->m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
	}

	EffectBase::Disable();
}

void LockPlayerInsideVehicleEffect::HandleTick() {
	EffectBase::HandleTick();

	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (!vehicle) {
		Disable();
	}
	else {
		Enable();
	}
}
