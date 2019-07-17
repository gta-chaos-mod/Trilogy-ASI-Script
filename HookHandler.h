#pragma once

#include "CPedDamageResponseCalculator.h"

#include "TruePacifist.h"
#include "LongLiveTheRich.h"
#include "InvisibleVehicles.h"
#include "RainbowCars.h"

class HookHandler
{
public:
	static void Initialize();

	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4);

	static void RenderVehicleEvent(CVehicle* vehicle);
};
