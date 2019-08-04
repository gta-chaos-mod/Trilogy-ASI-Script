#include "Timelapse.h"

Timelapse::Timelapse(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "timecycle") {}

void Timelapse::Enable() {
	CClock::ms_nMillisecondsPerGameMinute = 10;
}

void Timelapse::Disable() {
	CClock::ms_nMillisecondsPerGameMinute = 1000;

	TimedEffect::Disable();
}
