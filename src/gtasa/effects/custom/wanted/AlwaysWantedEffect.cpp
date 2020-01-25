#include "AlwaysWantedEffect.h"

AlwaysWantedEffect::AlwaysWantedEffect()
	: EffectBase("effect_always_wanted")
{
	AddType("wanted");
}

void AlwaysWantedEffect::HandleTick() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->CheatWantedLevel(4);
	}
}
