// Copyright (c) 2019 Lordmau5
#include "LetsTakeABreak.h"

LetsTakeABreak::LetsTakeABreak(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "controls") {}

void LetsTakeABreak::InitializeHooks() {
	HookCall(0x57C676, HookedOpenFile);

	HookCall(0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void LetsTakeABreak::Enable() {
	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}
}

void LetsTakeABreak::Disable() {
	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	TimedEffect::Disable();
}

int LetsTakeABreak::GetRemaining() {
	return effectRemaining >= 0 ? effectRemaining : remaining;
}

int LetsTakeABreak::GetDuration() {
	return rapidFire ? duration : effectDuration;
}

TimedEffect* LetsTakeABreak::SetRapidFire(bool is_rapid_fire) {
	if (is_rapid_fire) {
		duration = min(duration, effectDuration);
		effectRemaining = duration;
	}

	return TimedEffect::SetRapidFire(is_rapid_fire);
}

void LetsTakeABreak::HandleTick() {
	effectRemaining -= CalculateTick();
	if (effectRemaining <= 0) {
		Disable();
		return;
	}

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
	return 0;
}

#include "util/HookHandler.h"
void __fastcall LetsTakeABreak::HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		return;
	}

	HookHandler::HookedProcessMenuOptions(thisManager, edx, page);
}
