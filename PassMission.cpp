#include "PassMission.h"

bool PassMission::isEnabled = false;

PassMission::PassMission(int _duration, std::string _description)
	: EffectPlaceholder(_duration, _description) {}

void PassMission::InitializeHooks() {
	patch::RedirectCall(0x46DDED, HookedDebugGetKeyDown);
	patch::RedirectCall(0x46DE32, HookedDebugGetKeyDown);
}

void PassMission::Enable() {
	isEnabled = true;
}

void PassMission::Disable() {
	isEnabled = false;
}

void PassMission::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	Disable();
}

char __stdcall PassMission::HookedDebugGetKeyDown(int keyCode, int a2, int a3) {
	return isEnabled && keyCode == 83; // 83 / S for mission skip
}
