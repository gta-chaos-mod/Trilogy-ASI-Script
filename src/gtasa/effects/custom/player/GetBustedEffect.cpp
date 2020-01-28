#include "GetBustedEffect.h"

GetBustedEffect::GetBustedEffect()
	: EffectBase("effect_get_busted")
{
	if (Config::GetOrDefault("CrowdControl.Enabled", false)) {
		AddType("health");
	}
}

void GetBustedEffect::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	if (player && player->CanSetPedState()) {
		player->SetPedState(ePedState::PEDSTATE_ARRESTED);

		CCutsceneMgr::SkipCutscene();

		Disable();
	}
}
