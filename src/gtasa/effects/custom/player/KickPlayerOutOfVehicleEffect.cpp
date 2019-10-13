#include "KickPlayerOutOfVehicleEffect.h"

KickPlayerOutOfVehicleEffect::KickPlayerOutOfVehicleEffect()
	: EffectPlaceholder("effect_kick_player_out_of_vehicle") {}

void KickPlayerOutOfVehicleEffect::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
		if (playerVehicle) {
			player->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleCarSetPedOut(playerVehicle, 0, false), 0, false);
			if (!CTheScripts::IsPlayerOnAMission()) {
				playerVehicle->m_nVehicleFlags.bConsideredByPlayer = false;
			}
		}
	}
}
