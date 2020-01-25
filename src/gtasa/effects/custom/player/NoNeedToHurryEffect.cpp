#include "NoNeedToHurryEffect.h"

NoNeedToHurryEffect::NoNeedToHurryEffect()
	: EffectBase("effect_no_need_to_hurry")
{
	AddType("handling");
}

void NoNeedToHurryEffect::Disable() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		Command<eScriptCommands::COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER>(vehicle, 0.0f);
	}

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_pPlayerData->m_bPlayerSprintDisabled = false;
	}

	EffectBase::Disable();
}

void NoNeedToHurryEffect::HandleTick() {
	EffectBase::HandleTick();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		Command<eScriptCommands::COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER>(vehicle, 10.0f);
	}

	/*

	// Attack player
	if (vehicle->m_pDriver != FindPlayerPed()) {
		Command<eScriptCommands::COMMAND_SET_CAR_MISSION>(vehicle, eCarMission::MISSION_ATTACKPLAYER);
	}

	*/

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_pPlayerData->m_bPlayerSprintDisabled = true;
	}
}
