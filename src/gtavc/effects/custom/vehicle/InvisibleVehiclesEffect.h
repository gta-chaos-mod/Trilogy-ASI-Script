#pragma once

#include "util/EffectBase.h"

#include "CBike.h"
#include "CBoat.h"
#include "CHeli.h"
#include "CModelInfo.h"
#include "CPlane.h"
#include "CTrain.h"

class InvisibleVehiclesEffect : public EffectBase
{
public:
	InvisibleVehiclesEffect();

	void InitializeHooks() override;

	static void __fastcall HookedCAutomobileRender(CAutomobile* thisAutomobile);
	static void __fastcall HookedCBikeRender(CBike* thisBike);
	static void __fastcall HookedCPlaneRender(CPlane* thisPlane);
	static void __fastcall HookedCHeliRender(CHeli* thisHeli);
	static uint8_t* HookedRwIm3DTransform(uint8_t* pVerts, signed int numVerts, RwMatrix* ltm, unsigned int flags);
};
