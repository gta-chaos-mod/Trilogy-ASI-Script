#include "DisableRadarBlipsEffect.h"

DisableRadarBlipsEffect::DisableRadarBlipsEffect()
	: EffectBase("effect_disable_radar_blips")
{
	AddType("hud");
}

void DisableRadarBlipsEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	HookCall(0x49B34C, HookedBlipsDraw);
	HookCall(0x55AB18, HookedBlipsDraw);
}

void DisableRadarBlipsEffect::HookedBlipsDraw() {}
