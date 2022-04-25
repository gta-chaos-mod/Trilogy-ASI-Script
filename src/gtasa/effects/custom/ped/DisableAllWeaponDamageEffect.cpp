#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"

class DisableAllWeaponDamageEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x4B5B19, Hooked_AccountForPedArmour);
        injector::MakeCALL (0x4B5B27, Hooked_ComputeWillKillPed);

        for (int address : {0x73647F, 0x73B0BF, 0x73BEDD})
        {
            injector::MakeCALL (address, Hooked_VehicleInflictDamage);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    static void __fastcall Hooked_AccountForPedArmour (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageResponseInfo)
    {
    }

    static void __fastcall Hooked_ComputeWillKillPed (
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

    static void
    Hooked_VehicleInflictDamage (CVehicle *thisVehicle, void *edx, CPed *who,
                                 eWeaponType type, float damage, CVector coords)
    {
    }
};

DEFINE_EFFECT (DisableAllWeaponDamageEffect, "effect_disable_all_weapon_damage",
               GROUP_HEALTH);