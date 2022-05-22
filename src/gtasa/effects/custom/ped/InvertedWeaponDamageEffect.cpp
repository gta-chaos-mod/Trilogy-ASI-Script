#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <eWeaponType.h>

class InvertedWeaponDamageEffect : public EffectBase
{
    static const inline float DAMAGE_MULTIPLIER = 0.25f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        // CPedDamageResponseCalculator::ComputeWillKillPed
        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *,
                                uint8_t *, char),
                          0x4B5B27);
    }

    static void
    DamagePlayer (CPlayerPed *player, float damage)
    {
        damage *= DAMAGE_MULTIPLIER;

        float armourLeft  = player->m_fArmour - damage;
        player->m_fArmour = std::max (0.0f, armourLeft);
        if (armourLeft > 0.0f)
            damage = 0.0f;
        else
            damage = -armourLeft;

        float healthLeft  = player->m_fHealth - damage;
        player->m_fHealth = std::max (0.0f, healthLeft);
    }

    static void
    HealPlayer (CPlayerPed *player, float damage)
    {
        player->m_fHealth += damage;
        player->m_fHealth = std::min (player->m_fHealth, player->m_fMaxHealth);
    }

    static void
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, uint8_t *cDamageReponseInfo, char a4)
    {
        if (!thisCalc->m_pDamager
            || thisCalc->m_pDamager->m_nType != ENTITY_TYPE_PED)
        {
            cb ();
            return;
        }

        CPed *damager = (CPed *) thisCalc->m_pDamager;
        float damage  = thisCalc->m_fDamageFactor;

        CPlayerPed *player = FindPlayerPed ();
        if (damager == player && ped != player)
        {
            float previousPedHealth = ped->m_fHealth;
            cb ();
            float actualDamage = previousPedHealth - ped->m_fHealth;
            DamagePlayer (player, actualDamage);
        }
        else if (ped == player && damager != player)
        {
            HealPlayer (player, damage * 2.0f);
        }
    }
};

DEFINE_EFFECT (InvertedWeaponDamageEffect, "effect_inverted_weapon_damage",
               GROUP_HEALTH);