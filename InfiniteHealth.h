#pragma once

#include "TimedEffect.h"

#include "CPedDamageResponseCalculator.h"

class InfiniteHealth : public TimedEffect
{
public:
	static bool isEnabled;

public:
	InfiniteHealth(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

private:
	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4);

	static void __fastcall HookedKillPedsInVehicle(CVehicle* thisVehicle, void* edx);
	static void __fastcall HookedKillPedsGettingInVehicle(CVehicle* thisVehicle, void* edx);
};
