#pragma once

#include "util/EffectBase.h"

class DisableAllWeaponDamageEffect : public EffectBase
{
public:
	DisableAllWeaponDamageEffect();

	void InitializeHooks() override;

private:
	static bool __fastcall HookedCPedInflictDamage(CPed* thisPed, void* edx, CEntity* source, eWeaponType weapon, float damage, ePedPieceTypes pedPiece, uchar unknown);
	static bool __fastcall HookedCVehicleInflictDamage(CVehicle* thisVehicle, void* edx, CEntity* source, eWeaponType weapon, float damage, CVector hitPosition);
};
