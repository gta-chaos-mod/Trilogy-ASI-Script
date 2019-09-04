// Copyright (c) 2019 Lordmau5
#include "LagEffect.h"

LagEffect::LagEffect(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "game_speed") {}

void LagEffect::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
	*audioSpeed = 1.0f;

	TimedEffect::Disable();
}

void LagEffect::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	float scale = RandomHelper::Random(0.1f, 2.0f);
	CTimer::ms_fTimeScale = RandomHelper::Random(0.1f, 2.0f);

	float speed = max(0.5f, scale);
	if (speed > 1.0f) {
		speed = 1.0f + ((speed - 1.0f) * 0.175f);
	}
	*audioSpeed = speed;

	wait = RandomHelper::Random(50, 200);
}
