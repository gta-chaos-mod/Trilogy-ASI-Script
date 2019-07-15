#include "LagEffect.h"

LagEffect::LagEffect(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void LagEffect::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
}

void LagEffect::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	CTimer::ms_fTimeScale = Random(0.1f, 2.0f);
	wait = Random(50, 200);
}