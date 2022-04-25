#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"

class InfiniteHealthEveryoneEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x4B5B27, Hooked_ComputeWillKillPed);

        for (int address :
             {0x6B3950, 0x6B3D6C, 0x6BEAA3, 0x6C6F44, 0x6CCF83, 0x6F225A})
        {
            injector::MakeCALL (address, Hooked_KillPedsInVehicle);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_fHealth = player->m_fMaxHealth;

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bInvulnerable   = true;
            vehicle->m_nPhysicalFlags.bBulletProof    = true;
            vehicle->m_nPhysicalFlags.bCollisionProof = true;
            vehicle->m_nPhysicalFlags.bExplosionProof = true;
            vehicle->m_nPhysicalFlags.bFireProof      = true;
            vehicle->m_nPhysicalFlags.bMeeleProof     = true;
        }
    }

    static void __fastcall Hooked_ComputeWillKillPed (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageReponseInfo, char a4)
    {
    }

    static void __fastcall Hooked_KillPedsInVehicle (CVehicle *thisVehicle)
    {
        thisVehicle->m_nStatus = eEntityStatus::STATUS_SIMPLE;
    }
};

DEFINE_EFFECT (InfiniteHealthEveryoneEffect, "effect_infinite_health_everyone",
               GROUP_HEALTH);