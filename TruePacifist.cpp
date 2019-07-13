#include "TruePacifist.h"

static bool isEnabled = false;

TruePacifist::TruePacifist(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void TruePacifist::InitializeHooks() {
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);
}

void TruePacifist::Enable() {
	isEnabled = true;
}

void TruePacifist::Disable() {
	isEnabled = false;
}

void __fastcall TruePacifist::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo) {
	if (!isEnabled) {
		thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
	}
}

void __fastcall TruePacifist::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4) {
	if (!isEnabled) {
		thisCalc->ComputeWillKillPed(ped, a3, a4);
	}
}
