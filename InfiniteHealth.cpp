#include "InfiniteHealth.h"

bool InfiniteHealth::isEnabled = false;

InfiniteHealth::InfiniteHealth(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "health") {}

void InfiniteHealth::InitializeHooks() {
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);
}

void InfiniteHealth::Enable() {
	isEnabled = true;
}

void InfiniteHealth::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void __fastcall InfiniteHealth::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo) {
	thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
}

void __fastcall InfiniteHealth::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4) {
	if (isEnabled) {
		return;
	}

	thisCalc->ComputeWillKillPed(ped, a3, a4);
}
