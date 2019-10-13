#include "LetsTakeABreakEffect.h"

LetsTakeABreakEffect::LetsTakeABreakEffect()
	: EffectBase("effect_lets_take_a_break")
{
	SetEffectDuration(1000 * 10);
	AddType("controls");
}

void LetsTakeABreakEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x57C676, HookedOpenFile);

	HookCall(0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void LetsTakeABreakEffect::Enable() {
	EffectBase::Enable();

	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}
}

void LetsTakeABreakEffect::Disable() {
	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	EffectBase::Disable();
}

void LetsTakeABreakEffect::HandleTick() {
	EffectBase::HandleTick();

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

FILESTREAM LetsTakeABreakEffect::HookedOpenFile(const char* file, const char* mode) {
	return 0;
}

void __fastcall LetsTakeABreakEffect::HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		return;
	}

	GameFixes::HookedProcessMenuOptions(thisManager, edx, page);
}
