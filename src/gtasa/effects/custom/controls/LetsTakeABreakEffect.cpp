#include "LetsTakeABreakEffect.h"

LetsTakeABreakEffect::LetsTakeABreakEffect()
	: EffectBase("effect_lets_take_a_break")
{
	AddType("controls");
	SetEffectDuration(1000 * 10);
}

void LetsTakeABreakEffect::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player && player->GetPadFromPlayer()) {
		player->GetPadFromPlayer()->DisablePlayerControls = false;
	}

	EffectBase::Disable();
}

void LetsTakeABreakEffect::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	if (player && player->GetPadFromPlayer()) {
		player->GetPadFromPlayer()->DisablePlayerControls = true;
	}
}
