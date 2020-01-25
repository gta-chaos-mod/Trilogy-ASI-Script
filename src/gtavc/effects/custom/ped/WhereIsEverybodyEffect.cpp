#include "WhereIsEverybodyEffect.h"

WhereIsEverybodyEffect::WhereIsEverybodyEffect()
	: EffectBase("effect_where_is_everybody") {}

void WhereIsEverybodyEffect::InitializeHooks() {
	HookCall(0x4FE216, HookedCPedRender);
}

char __fastcall WhereIsEverybodyEffect::HookedCPedRender(CPed* thisPed) {
	return 0;
}
