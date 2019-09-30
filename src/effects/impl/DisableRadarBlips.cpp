// Copyright (c) 2019 Lordmau5
#include "DisableRadarBlips.h"

DisableRadarBlips::DisableRadarBlips(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "hud_blips") {}

void DisableRadarBlips::InitializeHooks() {
	HookJump(0x58AA2D, HookedBlipsDraw);
	HookCall(0x575B44, HookedBlipsDraw);
}

void DisableRadarBlips::HookedBlipsDraw() {}
