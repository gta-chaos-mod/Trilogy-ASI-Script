#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class InfiniteHealthPlayerEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *,
                                uint8_t *, char),
                          0x4B5B27);

        HOOK_METHOD_ARGS (inst, Hooked_KillPedsInVehicle, void (CVehicle *),
                          0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83,
                          0x6F225A);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_fHealth = player->m_fMaxHealth;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            vehicle->m_nPhysicalFlags.bInvulnerable   = true;
            vehicle->m_nPhysicalFlags.bBulletProof    = true;
            vehicle->m_nPhysicalFlags.bCollisionProof = true;
            vehicle->m_nPhysicalFlags.bExplosionProof = true;
            vehicle->m_nPhysicalFlags.bFireProof      = true;
            vehicle->m_nPhysicalFlags.bMeeleProof     = true;
        }
    }

    static void
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, uint8_t *cDamageResponseInfo, char a4)
    {
        if (ped == FindPlayerPed ()) return;

        cb ();
    }

    static void
    Hooked_KillPedsInVehicle (auto &&cb, CVehicle *thisVehicle)
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle && vehicle == thisVehicle)
        {
            thisVehicle->m_nStatus = STATUS_SIMPLE;
        }

        cb ();
    }
};

DEFINE_EFFECT (InfiniteHealthPlayerEffect, "effect_infinite_health_player",
               GROUP_HEALTH);