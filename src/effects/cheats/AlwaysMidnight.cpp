// Copyright (c) 2019 Lordmau5
#include "AlwaysMidnight.h"

AlwaysMidnight::AlwaysMidnight(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "timecycle") {}

void AlwaysMidnight::Disable() {
	*alwaysMidnightCheat = false;

	TimedEffect::Disable();
}

void AlwaysMidnight::HandleTick() {
	*alwaysMidnightCheat = true;

	CClock::ms_nGameClockHours = 0;
	CClock::ms_nGameClockMinutes = 0;
	CClock::ms_nGameClockSeconds = 0;
}
