#include "BigWheelsCheat.h"

BigWheelsCheat::BigWheelsCheat()
	: EffectPlaceholder("cheat_big_wheels") {}

void BigWheelsCheat::InitializeHooks() {
	HookCall(0x4AE78D, HookedCHudSetHelpMessage);
}

void BigWheelsCheat::Enable() {
	EffectPlaceholder::Enable();

	Call<0x4AE510>();
}

void BigWheelsCheat::HookedCHudSetHelpMessage(int a1, char a2, char a3) {}
