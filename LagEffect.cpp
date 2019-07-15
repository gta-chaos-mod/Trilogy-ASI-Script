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

	slow = !slow;
	if (slow) {
		CTimer::ms_fTimeScale = 0.25f;

		wait = Random(150, 250);
	}
	else {
		CTimer::ms_fTimeScale = 2.0f;

		wait = Random(350, 450);
	}
}