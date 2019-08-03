#include "DisableOneMovementKey.h"

bool DisableOneMovementKey::isEnabled = false;

DisableOneMovementKey::DisableOneMovementKey(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "controls") {}

void DisableOneMovementKey::InitializeHooks() {
	patch::RedirectCall(0x57C676, HookedOpenFile);
}

void DisableOneMovementKey::Enable() {
	isEnabled = true;

	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}

	// TODO: List of controller actions, pick one at random, disable it
	e_ControllerAction possibleActions[10] = {
		CA_GO_FORWARD,
		CA_GO_BACK,
		CA_GO_LEFT,
		CA_GO_RIGHT,
		CA_PED_SPRINT,
		CA_PED_JUMPING,
		CA_VEHICLE_ACCELERATE,
		CA_VEHICLE_BRAKE,
		CA_VEHICLE_STEERLEFT,
		CA_VEHICLE_STEERRIGHT
	};

	targetKey = possibleActions[RandomHelper::Random(0, 9)];
}

void DisableOneMovementKey::Disable() {
	isEnabled = false;

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}
}

void DisableOneMovementKey::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	ControlsManager.m_actions[targetKey] = CControllerAction();

	wait = 1000;
}

FILESTREAM DisableOneMovementKey::HookedOpenFile(const char* file, const char* mode) {
	return isEnabled ? 0 : CFileMgr::OpenFile(file, mode);
}
