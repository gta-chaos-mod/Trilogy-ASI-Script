// Copyright (c) 2019 Lordmau5
#include "DisableRadarBlips.h"

bool DisableRadarBlips::isEnabled = false;

DisableRadarBlips::DisableRadarBlips(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "hud_blips") {}

void DisableRadarBlips::InitializeHooks() {
	// Disable Radar Blips
	patch::RedirectJump(0x58AA2D, HookedBlipsDraw);
	patch::RedirectCall(0x575B44, HookedBlipsDraw);
}

void DisableRadarBlips::Enable() {
	isEnabled = true;
}

void DisableRadarBlips::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void DisableRadarBlips::HookedBlipsDraw() {
	if (!isEnabled) {
		CRadar::DrawBlips();
	}
}
