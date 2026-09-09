#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <eWeaponType.h>

class DisableAllWeaponDamageEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // CPedDamageResponseCalculator::ComputeWillKillPed
        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *,
                                uint8_t *, char),
                          0x4B5B27);

        // CPedDamageResponseCalculator::AccountForPedArmour
        HOOK_METHOD (inst, Hooked_Empty,
                     void (CPedDamageResponseCalculator *, CPed *, uint8_t *),
                     0x4B5B19);

        // CVehicle::InflictDamage
        HOOK_METHOD (inst, Hooked_Empty,
                     void (CVehicle *, CPed *, eWeaponType, float, CVector),
                     0x73647F, 0x73B0BF, 0x73BEDD);

        // CWeapon::GenerateDamageEvent (Police helicopter shots)
        HOOK (inst, Hooked_Empty,
              void (CPed *, CPed *, eWeaponType, int, int, char), 0x73B074);
    }

    static void
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, uint8_t *cDamageReponseInfo, char a4)
    {
        if (thisCalc->m_weaponType <= WEAPONTYPE_BRASSKNUCKLE
            || thisCalc->m_weaponType == WEAPONTYPE_PARACHUTE)
        {
            cb ();
            return;
        }

        if (thisCalc->m_pDamager
            && thisCalc->m_pDamager->m_nType == ENTITY_TYPE_PED)
        {
            return;
        }

        cb ();
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (DisableAllWeaponDamageEffect, "effect_disable_all_weapon_damage",
               GROUP_HEALTH);