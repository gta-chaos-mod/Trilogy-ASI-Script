#include "DisableRadarBlips.h"

static bool isEnabled = false;

DisableRadarBlips::DisableRadarBlips(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void DisableRadarBlips::InitializeHooks() {
	patch::RedirectJump(0x58AA2D, HookedBlipsDraw);
	patch::RedirectCall(0x575B44, HookedBlipsDraw);
}

void DisableRadarBlips::Enable() {
	isEnabled = true;
}

void DisableRadarBlips::Disable() {
	isEnabled = false;
}

void DisableRadarBlips::HookedBlipsDraw() {
	if (!isEnabled) {
		CRadar::DrawBlips();
	}
}