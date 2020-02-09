#pragma once

#include "util/EffectBase.h"
#include "util/CPedDamageResponseCalculator.h"

class DisableAllWeaponDamageEffect : public EffectBase
{
public:
    DisableAllWeaponDamageEffect ();

    void InitializeHooks () override;

private:
    static void __fastcall HookedAccountForPedArmour (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageReponseInfo);
    static void __fastcall HookedComputeWillKillPed (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageReponseInfo, char a4);
    static void __fastcall HookedVehicleInflictDamage (CVehicle *thisVehicle,
                                                       void *edx, CPed *who,
                                                       eWeaponType type,
                                                       float       damage,
                                                       CVector     coords);
};
