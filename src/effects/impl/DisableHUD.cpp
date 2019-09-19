// Copyright (c) 2019 Lordmau5
#include "DisableHUD.h"

bool DisableHUD::isEnabled = false;

DisableHUD::DisableHUD(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "hud_blips") {}

void DisableHUD::InitializeHooks() {
	// Disable HUD
	patch::RedirectCall(0x53E4FF, HookedHUDDraw);

	// Disable Radar Blips
	patch::RedirectJump(0x58AA2D, HookedBlipsDraw);
	patch::RedirectCall(0x575B44, HookedBlipsDraw);
}

void DisableHUD::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void DisableHUD::HandleTick() {
	isEnabled = true;
}

void DisableHUD::HookedHUDDraw() {
	if (isEnabled) {
		CRadar::Draw3dMarkers();
	}
	else {
		CHud::Draw();
	}
}

void DisableHUD::HookedBlipsDraw() {
	if (!isEnabled) {
		CRadar::DrawBlips();
	}
}
