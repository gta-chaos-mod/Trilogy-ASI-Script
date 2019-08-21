// Copyright (c) 2019 Lordmau5
#include "LetsTakeABreak.h"

bool LetsTakeABreak::isEnabled = false;

LetsTakeABreak::LetsTakeABreak(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "controls") {}

void LetsTakeABreak::InitializeHooks() {
	patch::RedirectCall(0x57C676, HookedOpenFile);
}

void LetsTakeABreak::Enable() {
	isEnabled = true;

	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}
}

void LetsTakeABreak::Disable() {
	isEnabled = false;

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	TimedEffect::Disable();
}

void LetsTakeABreak::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = CControllerAction();
	}

	wait = 1000;
}

FILESTREAM LetsTakeABreak::HookedOpenFile(const char* file, const char* mode) {
	return isEnabled ? 0 : CFileMgr::OpenFile(file, mode);
}
