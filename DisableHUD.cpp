#include "DisableHUD.h"

bool DisableHUD::isEnabled = false;

DisableHUD::DisableHUD(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "hud_blips") {}

void DisableHUD::InitializeHooks() {
	// Disable HUD
	patch::RedirectCall(0x53E4FF, HookedHUDDraw);

	// Disable Radar Blips
	patch::RedirectJump(0x58AA2D, HookedBlipsDraw);
	patch::RedirectCall(0x575B44, HookedBlipsDraw);
}

void DisableHUD::Enable() {
	isEnabled = true;
}

void DisableHUD::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
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
