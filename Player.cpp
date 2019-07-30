#include "Player.h"

void Player::GivePlayerHealthArmorMoney() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
		player->m_fArmour = 100.0f;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += 250000;
	}
}

void Player::ClearWeapons() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->ClearWeapons();
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
			playerVehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED;
		}
	}
}

void Player::LockPlayerInsideVehicle() {
	CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
	if (playerVehicle) {
		playerVehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED_PLAYER_INSIDE;
	}
}

void Player::SetMaxStamina() {
	CStats::SetStatValue(eStats::STAT_STAMINA, 1000.0f); // Stamina
}

void Player::SetMaxWeaponSkills() {
	CStats::SetStatValue(eStats::STAT_PISTOL_SKILL, 1000.0f); // Pistol
	CStats::SetStatValue(eStats::STAT_SILENCED_PISTOL_SKILL, 1000.0f); // Silenced pistol
	CStats::SetStatValue(eStats::STAT_DESERT_EAGLE_SKILL, 1000.0f); // Desert eagle
	CStats::SetStatValue(eStats::STAT_SHOTGUN_SKILL, 1000.0f); // Shotgun
	CStats::SetStatValue(eStats::STAT_SAWN_OFF_SHOTGUN_SKILL, 1000.0f); // Sawn-off shotgun
	CStats::SetStatValue(eStats::STAT_COMBAT_SHOTGUN_SKILL, 1000.0f); // Combat shotgun
	CStats::SetStatValue(eStats::STAT_MACHINE_PISTOL_SKILL, 1000.0f); // Machine pistol
	CStats::SetStatValue(eStats::STAT_SMG_SKILL, 1000.0f); // SMG
	CStats::SetStatValue(eStats::STAT_AK_47_SKILL, 1000.0f); // AK47
	CStats::SetStatValue(eStats::STAT_M4_SKILL, 1000.0f); // M4
	CStats::SetStatValue(eStats::STAT_RIFLE_SKILL, 1000.0f); // Rifle
}

void Player::SetMaxDrivingSkills() {
	CStats::SetStatValue(eStats::STAT_DRIVING_SKILL, 1000.0f); // Driving
	CStats::SetStatValue(eStats::STAT_FLYING_SKILL, 1000.0f); // Flying
	CStats::SetStatValue(eStats::STAT_BIKE_SKILL, 1000.0f); // Bike
	CStats::SetStatValue(eStats::STAT_CYCLING_SKILL, 1000.0f); // Cycling
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