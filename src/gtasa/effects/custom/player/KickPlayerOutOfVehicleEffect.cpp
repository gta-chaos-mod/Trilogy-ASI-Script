#include "KickPlayerOutOfVehicleEffect.h"

KickPlayerOutOfVehicleEffect::KickPlayerOutOfVehicleEffect()
	: EffectPlaceholder("effect_kick_player_out_of_vehicle") {}

bool KickPlayerOutOfVehicleEffect::CanActivate() {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);

	return vehicle != nullptr;
}

void KickPlayerOutOfVehicleEffect::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
		if (playerVehicle) {
			Command<eScriptCommands::COMMAND_TASK_LEAVE_CAR_IMMEDIATELY>(player, playerVehicle);
			if (!CTheScripts::IsPlayerOnAMission()) {
				playerVehicle->m_nVehicleFlags.bConsideredByPlayer = false;
			}
		}
	}
}
