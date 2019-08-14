#include "InfiniteHealth.h"

bool InfiniteHealth::isEnabled = false;

InfiniteHealth::InfiniteHealth(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "health") {}

void InfiniteHealth::InitializeHooks() {
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : {0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83, 0x6F225A}) {
		patch::RedirectCall(address, HookedKillPedsInVehicle);
	}

	patch::RedirectCall(0x6B3957, HookedKillPedsGettingInVehicle);
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

void __fastcall InfiniteHealth::HookedKillPedsInVehicle(CVehicle* thisVehicle, void* edx) {
	// TODO: Can't exit vehicle if vehicle blew up and player isn't dead
	//if (isEnabled) {
	//	return;
	//}

	thisVehicle->KillPedsInVehicle();
}

void __fastcall InfiniteHealth::HookedKillPedsGettingInVehicle(CVehicle* thisVehicle, void* edx) {
	// TODO: Can't exit vehicle if vehicle blew up and player isn't dead
	//if (isEnabled) {
	//	return;
	//}

	thisVehicle->KillPedsGettingInVehicle();
}
