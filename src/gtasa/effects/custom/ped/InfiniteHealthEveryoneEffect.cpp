#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class InfiniteHealthEveryoneEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_KillPedsInVehicle, void (CVehicle *),
                          0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83,
                          0x6F225A);

        // CPedDamageResponseCalculator::ComputeWillKillPed
        HOOK_METHOD (inst, Hooked_Empty,
                     void (CPedDamageResponseCalculator *, CPed *, uint8_t *,
                           char),
                     0x4B5B27);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_fHealth = player->m_fMaxHealth;

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (!vehicle || !vehicle->m_pDriver) continue;

            vehicle->m_nPhysicalFlags.bInvulnerable   = true;
            vehicle->m_nPhysicalFlags.bBulletProof    = true;
            vehicle->m_nPhysicalFlags.bCollisionProof = true;
            vehicle->m_nPhysicalFlags.bExplosionProof = true;
            vehicle->m_nPhysicalFlags.bFireProof      = true;
            vehicle->m_nPhysicalFlags.bMeleeProof     = true;
        }
    }

    static void
    Hooked_KillPedsInVehicle (auto &&cb, CVehicle *thisVehicle)
    {
        thisVehicle->m_nStatus = STATUS_SIMPLE;
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (InfiniteHealthEveryoneEffect, "effect_infinite_health_everyone",
               GROUP_HEALTH);