// Copyright (c) 2019 Lordmau5
#include "Player.h"

void Player::GivePlayerHealthArmorMoney() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
		player->m_fArmour = 100.0f;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += 250000;

		CVehicle* vehicle = FindPlayerVehicle(-1, false);
		if (vehicle) {
			bool isHigherDurability = vehicle->m_fHealth > 1000.0f;
			vehicle->Fix();
			vehicle->m_fHealth = isHigherDurability ? 10000.0f : 1000.0f;
		}
	}
}

void Player::KillPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = 0.0f;
	}
}

void Player::KickOutOfVehicleAndLock() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
		if (playerVehicle) {
			player->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleCarSetPedOut(playerVehicle, 0, false), 0, false);
			playerVehicle->m_nVehicleFlags.bConsideredByPlayer = false;
		}
	}
}

void Player::SetStamina(bool isMax) {
	float value = isMax ? 1000.0f : 0.0f;

	CStats::SetStatValue(eStats::STAT_STAMINA, value); // Stamina
}

void Player::NoStamina() {
	SetStamina(false);
}

void Player::MaxStamina() {
	SetStamina(true);
}

void Player::SetWeaponSkills(bool isMax) {
	float value = isMax ? 1000.0f : 0.0f;

	CStats::SetStatValue(eStats::STAT_PISTOL_SKILL, value); // Pistol
	CStats::SetStatValue(eStats::STAT_SILENCED_PISTOL_SKILL, value); // Silenced pistol
	CStats::SetStatValue(eStats::STAT_DESERT_EAGLE_SKILL, value); // Desert eagle
	CStats::SetStatValue(eStats::STAT_SHOTGUN_SKILL, value); // Shotgun
	CStats::SetStatValue(eStats::STAT_SAWN_OFF_SHOTGUN_SKILL, value); // Sawn-off shotgun
	CStats::SetStatValue(eStats::STAT_COMBAT_SHOTGUN_SKILL, value); // Combat shotgun
	CStats::SetStatValue(eStats::STAT_MACHINE_PISTOL_SKILL, value); // Machine pistol
	CStats::SetStatValue(eStats::STAT_SMG_SKILL, value); // SMG
	CStats::SetStatValue(eStats::STAT_AK_47_SKILL, value); // AK47
	CStats::SetStatValue(eStats::STAT_M4_SKILL, value); // M4
	CStats::SetStatValue(eStats::STAT_RIFLE_SKILL, value); // Rifle
}

void Player::NoWeaponSkills() {
	SetWeaponSkills(false);
}

void Player::MaxWeaponSkills() {
	SetWeaponSkills(true);
}

void Player::SetDrivingSkills(bool isMax) {
	float value = isMax ? 1000.0f : 0.0f;

	CStats::SetStatValue(eStats::STAT_DRIVING_SKILL, value); // Driving
	CStats::SetStatValue(eStats::STAT_FLYING_SKILL, value); // Flying
	CStats::SetStatValue(eStats::STAT_BIKE_SKILL, value); // Bike
	CStats::SetStatValue(eStats::STAT_CYCLING_SKILL, value); // Cycling
}

void Player::NoDrivingSkills() {
	SetDrivingSkills(false);
}

void Player::MaxDrivingSkills() {
	SetDrivingSkills(true);
}

void Player::DoBusted() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->SetPedState(ePedState::PEDSTATE_ARRESTED);
	}
}

void Player::DoWasted() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->SetPedState(ePedState::PEDSTATE_DEAD);
	}
}
