#include "DisableHUDEffect.h"

DisableHUDEffect::DisableHUDEffect()
	: EffectBase("effect_disable_hud")
{
	AddType("hud");
}

void DisableHUDEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x4A64D0, HookedHUDDraw);
}

void DisableHUDEffect::HookedHUDDraw() {}
