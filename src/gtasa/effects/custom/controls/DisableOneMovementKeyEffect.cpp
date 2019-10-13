#include "DisableOneMovementKeyEffect.h"

DisableOneMovementKeyEffect::DisableOneMovementKeyEffect()
	: EffectBase("effect_disable_one_movement_key")
{
	AddType("controls");
}

void DisableOneMovementKeyEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x57C676, HookedOpenFile);

	HookCall(0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void DisableOneMovementKeyEffect::Enable() {
	EffectBase::Enable();

	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}

	targetAction = possibleActions[RandomHelper::Random(0, 3)];
}

void DisableOneMovementKeyEffect::Disable() {
	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	EffectBase::Disable();
}

void DisableOneMovementKeyEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	ControlsManager.m_actions[targetAction.first] = CControllerAction();
	ControlsManager.m_actions[targetAction.second] = CControllerAction();

	wait = 1000;
}

FILESTREAM DisableOneMovementKeyEffect::HookedOpenFile(const char* file, const char* mode) {
	return 0;
}

void __fastcall DisableOneMovementKeyEffect::HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		return;
	}

	GameFixes::HookedProcessMenuOptions(thisManager, edx, page);
}
