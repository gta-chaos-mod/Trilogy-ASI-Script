#include "DisableHUD.h"

static bool isEnabled = false;

DisableHUD::DisableHUD(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void DisableHUD::InitializeHooks() {
	patch::RedirectCall(0x53E4FF, HookedHUDDraw);
}

void DisableHUD::Enable() {
	isEnabled = true;
}

void DisableHUD::Disable() {
	isEnabled = false;
}

void DisableHUD::HookedHUDDraw() {
	if (isEnabled) {
		CRadar::Draw3dMarkers();
	}
	else {
		CHud::Draw();
	}
}