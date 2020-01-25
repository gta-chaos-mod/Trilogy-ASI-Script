#pragma once

#include "effects/TimedAddressEffect.h"

#include "CCarCtrl.h"

class MegaPunchCheat : public TimedAddressEffect
{
public:
	MegaPunchCheat();

	void InitializeHooks() override;

	static void __fastcall HookedFightHitCar(CTaskSimpleFight* thisTask, void* edx, CPed* ped, CVehicle* vehicle, CVector* colCoord, CVector* colDir, int colComp, int a7);
};
