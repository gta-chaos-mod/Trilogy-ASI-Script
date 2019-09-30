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
			float setHealth = vehicle->m_fHealth > 1000.0f ? 100000.0f : 1000.0f;
			vehicle->Fix();
			vehicle->m_fHealth = setHealth;
		}
	}
}

void Player::WeaponSet4() {
	CPlayerPed* player = FindPlayerPed();
	if (!player) {
		return;
	}

	bool hasNightVision = player->DoWeHaveWeaponAvailable(WEAPON_NIGHTVISION);

	CStreaming::RequestModel(MODEL_MINIGUN, 2); // Minigun
	CStreaming::RequestModel(MODEL_GUN_DILDO2, 2); // Dildo 2
	CStreaming::RequestModel(hasNightVision ? MODEL_IRGOGGLES : MODEL_NVGOGGLES, 2); // Thermal Vision / Night Vision
	CStreaming::LoadAllRequestedModels(0);

	player->GiveWeapon(WEAPON_MINIGUN, 500, 1);
	player->GiveWeapon(WEAPON_DILDO2, 1, 1);
	player->GiveWeapon(hasNightVision ? WEAPON_INFRARED : WEAPON_NIGHTVISION, 1, 1);

	CStreaming::SetModelIsDeletable(MODEL_MINIGUN);
	CStreaming::SetModelIsDeletable(MODEL_GUN_DILDO2);
	CStreaming::SetModelIsDeletable(hasNightVision ? MODEL_IRGOGGLES : MODEL_NVGOGGLES);
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

void Player::MakeFat() {
	CStats::SetStatValue(eStats::STAT_FAT, 1000.0f);

	RebuildPlayer();
}

void Player::MakeMuscle() {
	CStats::SetStatValue(eStats::STAT_MUSCLE, 1000.0f);

	RebuildPlayer();
}

void Player::MakeSkinny() {
	CStats::SetStatValue(eStats::STAT_FAT, 0.0f);
	CStats::SetStatValue(eStats::STAT_MUSCLE, 0.0f);

	RebuildPlayer();
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

void Player::RemoveBalaclava() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CPedClothesDesc* clothes = player->m_pPlayerData->m_pPedClothesDesc;
		if (clothes && clothes->GetIsWearingBalaclava()) {
			clothes->SetTextureAndModel((unsigned int)0, (unsigned int)0, 17);
			RebuildPlayer();
		}
	}
}

void Player::RebuildPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		ePedState oldState = player->m_nPedState;
		player->m_nPedState = ePedState::PEDSTATE_IDLE;
		CClothes::RebuildPlayer(player, false);
		player->m_nPedState = oldState;
	}
}
