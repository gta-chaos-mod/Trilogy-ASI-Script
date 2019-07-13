#include "Timelapse.h"

Timelapse::Timelapse(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void Timelapse::Enable() {
	CClock::ms_nMillisecondsPerGameMinute = 10;
}

void Timelapse::Disable() {
	CClock::ms_nMillisecondsPerGameMinute = 1000;
}