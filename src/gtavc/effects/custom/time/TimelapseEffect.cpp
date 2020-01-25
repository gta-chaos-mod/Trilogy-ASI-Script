#include "TimelapseEffect.h"

TimelapseEffect::TimelapseEffect()
	: EffectBase("effect_timelapse")
{
	AddType("time");
}

void TimelapseEffect::Disable() {
	CClock::ms_nMillisecondsPerGameMinute = 1000;

	EffectBase::Disable();
}

void TimelapseEffect::HandleTick() {
	EffectBase::HandleTick();

	CClock::ms_nMillisecondsPerGameMinute = 10;
}
