// Copyright (c) 2019 Lordmau5
#include "InvertedControls.h"

bool InvertedControls::isEnabled = false;

InvertedControls::InvertedControls(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "controls") {}

void InvertedControls::InitializeHooks() {
	patch::RedirectCall(0x57C676, HookedOpenFile);
}

void InvertedControls::Enable() {
	isEnabled = true;

	for (int i = 0; i < 59; i++) {
		origActions[i] = invertedActions[i] = ControlsManager.m_actions[i];
	}

	SwapControls(e_ControllerAction::CA_PED_FIREWEAPON, e_ControllerAction::CA_PED_LOCK_TARGET);
	SwapControls(e_ControllerAction::CA_GO_FORWARD, e_ControllerAction::CA_GO_BACK);
	SwapControls(e_ControllerAction::CA_GO_LEFT, e_ControllerAction::CA_GO_RIGHT);
	SwapControls(e_ControllerAction::CA_PED_SNIPER_ZOOM_IN, e_ControllerAction::CA_PED_SNIPER_ZOOM_OUT);
	SwapControls(e_ControllerAction::CA_PED_SPRINT, e_ControllerAction::CA_PED_JUMPING);
	SwapControls(e_ControllerAction::CA_PED_CYCLE_TARGET_LEFT, e_ControllerAction::CA_PED_CYCLE_TARGET_RIGHT);
	SwapControls(e_ControllerAction::CA_CONVERSATION_YES, e_ControllerAction::CA_CONVERSATION_NO);
	SwapControls(e_ControllerAction::CA_GROUP_CONTROL_FWD, e_ControllerAction::CA_GROUP_CONTROL_BWD);

	SwapControls(e_ControllerAction::CA_VEHICLE_ACCELERATE, e_ControllerAction::CA_VEHICLE_BRAKE);
	SwapControls(e_ControllerAction::CA_VEHICLE_STEERLEFT, e_ControllerAction::CA_VEHICLE_STEERRIGHT);
	SwapControls(e_ControllerAction::CA_VEHICLE_STEERUP, e_ControllerAction::CA_VEHICLE_STEERDOWN);
	SwapControls(e_ControllerAction::CA_VEHICLE_LOOKLEFT, e_ControllerAction::CA_VEHICLE_LOOKRIGHT);
	SwapControls(e_ControllerAction::CA_VEHICLE_TURRETUP, e_ControllerAction::CA_VEHICLE_TURRETDOWN);
	SwapControls(e_ControllerAction::CA_VEHICLE_TURRETLEFT, e_ControllerAction::CA_VEHICLE_TURRETRIGHT);
	SwapControls(e_ControllerAction::CA_VEHICLE_HANDBRAKE, e_ControllerAction::CA_VEHICLE_HORN);
}

void InvertedControls::Disable() {
	isEnabled = false;

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	TimedEffect::Disable();
}

void InvertedControls::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = invertedActions[i];
	}

	wait = 1000;
}

FILESTREAM InvertedControls::HookedOpenFile(const char* file, const char* mode) {
	return isEnabled ? 0 : CFileMgr::OpenFile(file, mode);
}

void InvertedControls::SwapControls(e_ControllerAction target, e_ControllerAction source) {
	invertedActions[(int)target] = origActions[(int)source];
	invertedActions[(int)source] = origActions[(int)target];
}
