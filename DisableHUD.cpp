#include "DisableHUD.h"

static bool isHooked = false;
static bool isEnabled = false;

DisableHUD::DisableHUD(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void DisableHUD::InitializeHooks() {
	if (isHooked) {
		return;
	}

	patch::RedirectCall(0x53E4FF, HookedHUDDraw);

	isHooked = true;
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