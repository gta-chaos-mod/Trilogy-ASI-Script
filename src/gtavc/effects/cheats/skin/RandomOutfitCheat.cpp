#include "RandomOutfitCheat.h"

RandomOutfitCheat::RandomOutfitCheat()
	: EffectPlaceholder("cheat_random_outfit") {}

void RandomOutfitCheat::InitializeHooks() {
	HookCall(0x4AE7F5, HookedCHudSetHelpMessage);
}

void RandomOutfitCheat::Enable() {
	EffectPlaceholder::Enable();

	Call<0x4AE7B0>();
}

void RandomOutfitCheat::HookedCHudSetHelpMessage(int a1, char a2, char a3) {}
