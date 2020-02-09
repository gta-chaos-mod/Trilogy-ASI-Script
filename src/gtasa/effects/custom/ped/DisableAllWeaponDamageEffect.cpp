#include "DisableAllWeaponDamageEffect.h"

DisableAllWeaponDamageEffect::DisableAllWeaponDamageEffect ()
    : EffectBase ("effect_disable_all_weapon_damage")
{
    AddType ("health");
}

void
DisableAllWeaponDamageEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x4B5B19, HookedAccountForPedArmour);
    HookCall (0x4B5B27, HookedComputeWillKillPed);

    for (int address : {0x73647F, 0x73B0BF, 0x73BEDD})
    {
        HookCall (address, HookedVehicleInflictDamage);
    }
}

void __fastcall DisableAllWeaponDamageEffect::HookedAccountForPedArmour (
    CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
    uint8_t *cDamageResponseInfo)
{
}

void __fastcall DisableAllWeaponDamageEffect::HookedComputeWillKillPed (
    CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
    uint8_t *cDamageReponseInfo, char a4)
{
    if (thisCalc->m_weaponType <= eWeaponType::WEAPON_BRASSKNUCKLE
        || thisCalc->m_weaponType == eWeaponType::WEAPON_PARACHUTE)
    {
        thisCalc->ComputeWillKillPed (ped, cDamageReponseInfo, a4);
        return;
    }

    if (thisCalc->m_pDamager
        && thisCalc->m_pDamager->m_nType == eEntityType::ENTITY_TYPE_PED)
    {
        return;
    }

    thisCalc->ComputeWillKillPed (ped, cDamageReponseInfo, a4);
}

void
DisableAllWeaponDamageEffect::HookedVehicleInflictDamage (CVehicle *thisVehicle,
                                                          void *edx, CPed *who,
                                                          eWeaponType type,
                                                          float       damage,
                                                          CVector     coords)
{
}
