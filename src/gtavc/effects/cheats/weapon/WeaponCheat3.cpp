#include "WeaponCheat3.h"

WeaponCheat3::WeaponCheat3()
	: EffectPlaceholder("cheat_weapons_3") {}

void WeaponCheat3::InitializeHooks() {
	HookCall(0x4AEAE4, HookedCHudSetHelpMessage);
}

void WeaponCheat3::Enable() {
	EffectPlaceholder::Enable();

	Call<0x4AEAD0>();
}

void WeaponCheat3::HookedCHudSetHelpMessage(int a1, char a2, char a3) {}
