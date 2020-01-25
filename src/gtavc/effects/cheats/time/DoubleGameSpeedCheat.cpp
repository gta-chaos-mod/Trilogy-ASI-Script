#include "DoubleGameSpeedCheat.h"

DoubleGameSpeedCheat::DoubleGameSpeedCheat()
	: EffectBase("cheat_double_game_speed")
{
	AddType("game_speed");
}

void DoubleGameSpeedCheat::Disable() {
	CTimer::ms_fTimeScale = 1.0f;

	EffectBase::Disable();
}

void DoubleGameSpeedCheat::HandleTick() {
	EffectBase::HandleTick();

	CTimer::ms_fTimeScale = 2.0f;
}
