#include "HalfGameSpeedCheat.h"

HalfGameSpeedCheat::HalfGameSpeedCheat()
	: EffectBase("cheat_half_game_speed")
{
	AddType("game_speed");
}

EffectBase* HalfGameSpeedCheat::SetEffectDuration(int duration) {
	EffectBase::SetEffectDuration(duration / 3 * 2);
	return this;
}

void HalfGameSpeedCheat::Disable() {
	CTimer::ms_fTimeScale = 1.0f;

	EffectBase::Disable();
}

void HalfGameSpeedCheat::HandleTick() {
	EffectBase::HandleTick();

	CTimer::ms_fTimeScale = 0.5f;
}
