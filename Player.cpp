#include "Player.h"

void Player::GivePlayerHealthArmorMoney() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
		player->m_fArmour = 100.0f;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += 250000;
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
		if (player->m_pVehicle) {
			player->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleCarSetPedOut(player->m_pVehicle, 0, false), 0, false);
			player->m_pVehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED;
		}
	}
}

void Player::LockPlayerInsideVehicle() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		if (player->m_pVehicle) {
			player->m_pVehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED_PLAYER_INSIDE;
		}
	}
}

void Player::SetMaxStamina() {
	*(reinterpret_cast<float*>(0xB793D8)) = 1000.0f; // Stamina
}

void Player::SetMaxWeaponSkills() {
	*(reinterpret_cast<float*>(0xB79494)) = 1000.0f; // Pistol
	*(reinterpret_cast<float*>(0xB79498)) = 1000.0f; // Silenced pistol
	*(reinterpret_cast<float*>(0xB7949C)) = 1000.0f; // Desert eagle
	*(reinterpret_cast<float*>(0xB794A0)) = 1000.0f; // Shotgun
	*(reinterpret_cast<float*>(0xB794A4)) = 1000.0f; // Sawn-off shotgun
	*(reinterpret_cast<float*>(0xB794A8)) = 1000.0f; // Combat shotgun
	*(reinterpret_cast<float*>(0xB794AC)) = 1000.0f; // Machine pistol
	*(reinterpret_cast<float*>(0xB794B0)) = 1000.0f; // SMG
	*(reinterpret_cast<float*>(0xB794B4)) = 1000.0f; // AK47
	*(reinterpret_cast<float*>(0xB794B8)) = 1000.0f; // M4
}

void Player::SetMaxDrivingSkills() {
	*(reinterpret_cast<float*>(0xB790A0)) = 1000.0f; // Driving
	*(reinterpret_cast<float*>(0xB7919C)) = 1000.0f; // Flying
	*(reinterpret_cast<float*>(0xB791B4)) = 1000.0f; // Bike
	*(reinterpret_cast<float*>(0xB791B8)) = 1000.0f; // Cycling
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