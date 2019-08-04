#pragma once

#include "DisableHUD.h"
#include "DisableOneMovementKey.h"
#include "DisableRadarBlips.h"
#include "InfiniteHealth.h"
#include "InvertedControls.h"
#include "InvisibleVehicles.h"
#include "LetsTakeABreak.h"
#include "LongLiveTheRich.h"
#include "RainbowCars.h"
#include "TruePacifist.h"

#include "CMenuManager.h"
#include "CPedDamageResponseCalculator.h"

class HookHandler
{
public:
	static bool canLoadSave;

public:
	static void Initialize();

	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4);

	static void RenderVehicleEvent(CVehicle* vehicle);

	static void HookedHUDDraw();
	static void HookedBlipsDraw();

	static void __fastcall HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
