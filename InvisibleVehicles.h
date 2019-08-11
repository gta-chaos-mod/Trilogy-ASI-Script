#pragma once

#include "TimedEffect.h"

#include "CBike.h"
#include "CBmx.h"
#include "CHeli.h"
#include "CModelInfo.h"
#include "CPlane.h"
#include "CShadows.h"

class InvisibleVehicles : public TimedEffect
{
public:
	static bool* isEnabled;

public:
	InvisibleVehicles(int duration, std::string description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

	static void TryRenderAtomic(RwFrame* frame);

	static void __fastcall HookedRenderHeli(CHeli* thisHeli, void* edx);
	static void __fastcall HookedRenderBike(CBike* thisBike, void* edx);
	static void __fastcall HookedRenderPlane(CPlane* thisPlane, void* edx);
	static void __fastcall HookedRenderEffects(CEntity* thisEntity, void* edx);
	static void HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType);
};
