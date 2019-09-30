// Copyright (c) 2019 Lordmau5
#include "DisableOneMovementKey.h"

DisableOneMovementKey::DisableOneMovementKey(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "controls") {}

void DisableOneMovementKey::InitializeHooks() {
	HookCall(0x57C676, HookedOpenFile);

	HookCall(0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void DisableOneMovementKey::Enable() {
	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}

	possibleActions.push_back(std::make_pair(CA_GO_FORWARD, CA_VEHICLE_ACCELERATE));
	possibleActions.push_back(std::make_pair(CA_GO_BACK, CA_VEHICLE_BRAKE));
	possibleActions.push_back(std::make_pair(CA_GO_LEFT, CA_VEHICLE_STEERLEFT));
	possibleActions.push_back(std::make_pair(CA_GO_RIGHT, CA_VEHICLE_STEERRIGHT));

	targetAction = possibleActions[RandomHelper::Random(0, 4)];
}

void DisableOneMovementKey::Disable() {
	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	TimedEffect::Disable();
}

void DisableOneMovementKey::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	ControlsManager.m_actions[targetAction.first] = CControllerAction();
	ControlsManager.m_actions[targetAction.second] = CControllerAction();

	wait = 1000;
}

FILESTREAM DisableOneMovementKey::HookedOpenFile(const char* file, const char* mode) {
	return 0;
}

#include "util/HookHandler.h"
void __fastcall DisableOneMovementKey::HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		return;
	}

	HookHandler::HookedProcessMenuOptions(thisManager, edx, page);
}
