#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

template <float dmgMult> class DeadlyBulletsEffect : public EffectBase
{
    bool isPlayerOnly = false;

public:
    DeadlyBulletsEffect (bool playerOnly) : isPlayerOnly (playerOnly) {}

    void
    OnStart (EffectInstance *inst) override
    {
        if (!isPlayerOnly)
        {
            HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed_everyone,
                              void (CPedDamageResponseCalculator *, CPed *,
                                    uint8_t *, char),
                              0x4B5B27);

            HOOK_METHOD_ARGS (inst, Hooked_VehicleInflictDamage_everyone,
                              void (CVehicle *, CEntity *, eWeaponType, float,
                                    CVector),
                              0x6D7C90);
        }
        else
        {
            HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed_player,
                              void (CPedDamageResponseCalculator *, CPed *,
                                    uint8_t *, char),
                              0x4B5B27);

            HOOK_METHOD_ARGS (inst, Hooked_VehicleInflictDamage_player,
                              void (CVehicle *, CEntity *, eWeaponType, float,
                                    CVector),
                              0x6D7C90);
        }
    }

    static void
    Hooked_VehicleInflictDamage_player (auto &&cb, CVehicle *self,
                                        CEntity *damager, eWeaponType type,
                                        float intensity, CVector coords)
    {
        cb ();

        if (damager != FindPlayerPed ()) return;

        if (!self || self->m_nPhysicalFlags.bBulletProof) return;

        if (type >= WEAPON_PISTOL && type <= WEAPON_SNIPERRIFLE)
        {
            float mult = std::abs (dmgMult - 1.0f);
            self->m_fHealth -= (intensity * mult);
        }
    }

    static void
    Hooked_VehicleInflictDamage_everyone (auto &&cb, CVehicle *self,
                                          CEntity *damager, eWeaponType type,
                                          float intensity, CVector coords)
    {
        cb ();

        if (!self || self->m_nPhysicalFlags.bBulletProof) return;

        if (type >= WEAPON_PISTOL && type <= WEAPON_SNIPERRIFLE)
        {
            float mult = std::abs (dmgMult - 1.0f);
            self->m_fHealth -= (intensity * mult);
        }
    }

    static void
    Hooked_ComputeWillKillPed_player (auto                        &&cb,
                                      CPedDamageResponseCalculator *thisCalc,
                                      CPed *ped, uint8_t *cDamageResponseInfo,
                                      char a4)
    {
        if (thisCalc->m_pDamager != FindPlayerPed ()) return;

        if (thisCalc->m_weaponType >= WEAPON_PISTOL
            && thisCalc->m_weaponType <= WEAPON_SNIPERRIFLE)
        {
            thisCalc->m_fDamageFactor *= dmgMult;
        }

        cb ();
    }

    static void
    Hooked_ComputeWillKillPed_everyone (auto                        &&cb,
                                        CPedDamageResponseCalculator *thisCalc,
                                        CPed *ped, uint8_t *cDamageResponseInfo,
                                        char a4)
    {
        if (thisCalc->m_weaponType >= WEAPON_PISTOL
            && thisCalc->m_weaponType <= WEAPON_SNIPERRIFLE)
        {
            thisCalc->m_fDamageFactor *= dmgMult;
        }

        cb ();
    }
};

using DeadlyBulletsEffectQuad = DeadlyBulletsEffect<4.0f>;

/* clang-format off */
DEFINE_EFFECT (DeadlyBulletsEffectQuad, "effect_deadly_bullets_quad_dmg_everyone",
               GROUP_WEAPONS, false);
DEFINE_EFFECT (DeadlyBulletsEffectQuad, "effect_deadly_bullets_quad_dmg_player",
               GROUP_WEAPONS, true);
/* clang-format on */