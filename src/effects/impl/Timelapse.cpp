// Copyright (c) 2019 Lordmau5
#include "Timelapse.h"

Timelapse::Timelapse(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "timecycle") {}

void Timelapse::Disable() {
	CClock::ms_nMillisecondsPerGameMinute = 1000;

	TimedEffect::Disable();
}

void Timelapse::HandleTick() {
	CClock::ms_nMillisecondsPerGameMinute = 10;
}
