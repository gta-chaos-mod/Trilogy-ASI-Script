#include "LagEffect.h"

LagEffect::LagEffect(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void LagEffect::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
}

void LagEffect::HandleTick() {
	if (wait > 0) {
		wait -= (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
		return;
	}

	std::default_random_engine re;

	slow = !slow;
	if (slow) {
		CTimer::ms_fTimeScale = 0.25f;

		std::uniform_int_distribution unif_i(150, 250);
		wait = unif_i(re);
	}
	else {
		CTimer::ms_fTimeScale = 2.0f;

		std::uniform_int_distribution unif_i(350, 450);
		wait = unif_i(re);
	}
}