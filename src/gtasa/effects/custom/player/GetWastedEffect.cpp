#include "GetWastedEffect.h"

GetWastedEffect::GetWastedEffect()
	: EffectPlaceholder("effect_get_wasted")
{
	if (Config::GetOrDefault("CrowdControl.Enabled", false)) {
		AddType("health");
	}
}

void GetWastedEffect::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->SetPedState(ePedState::PEDSTATE_DEAD);

		CCutsceneMgr::SkipCutscene();
	}
}
