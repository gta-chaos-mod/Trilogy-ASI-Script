#include "GetBustedEffect.h"

GetBustedEffect::GetBustedEffect()
	: EffectPlaceholder("effect_get_busted") {}

void GetBustedEffect::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->SetPedState(ePedState::PEDSTATE_ARRESTED);
	}
}
