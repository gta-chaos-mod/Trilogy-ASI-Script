#include "DisableRadarBlips.h"

bool DisableRadarBlips::isEnabled = false;

DisableRadarBlips::DisableRadarBlips(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void DisableRadarBlips::Enable() {
	isEnabled = true;
}

void DisableRadarBlips::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}
