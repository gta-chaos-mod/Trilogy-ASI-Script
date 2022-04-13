#include <util/EffectBase.h>

using namespace plugin;

static ThiscallEvent<
    AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL, 0x54C435,
                H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL, 0x54D3FE, H_CALL,
                0x54D4D2, H_CALL>,
    PRIORITY_AFTER,
    ArgPick<ArgTypes<CVehicle *, CVehicle *, int, float *, int>, 0, 1, 2, 3, 4>,
    void (CVehicle *, CVehicle *, int, float *, int)>
    applyCollisionEvent;

class SmashNBoomEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        applyCollisionEvent += ApplyCollision;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        applyCollisionEvent -= ApplyCollision;

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle)
            {
                vehicle->m_nPhysicalFlags.bInvulnerable   = false;
                vehicle->m_nPhysicalFlags.bExplosionProof = false;
                vehicle->m_nPhysicalFlags.bFireProof      = false;
                vehicle->m_nPhysicalFlags.bCollisionProof = false;
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle)
            {
                bool proof = (player && player->m_pVehicle == vehicle
                              && player->m_pVehicle->IsDriver (player));
                vehicle->m_nPhysicalFlags.bInvulnerable   = proof;
                vehicle->m_nPhysicalFlags.bExplosionProof = proof;
                vehicle->m_nPhysicalFlags.bFireProof      = proof;
                vehicle->m_nPhysicalFlags.bCollisionProof = proof;
            }
        }
    }

    static void
    ApplyCollision (CVehicle *thisVehicle, CVehicle *otherVehicle, int a3,
                    float *a4, int a5)
    {
        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (!playerVehicle)
            return;

        if (playerVehicle == thisVehicle)
        {
            otherVehicle->m_nPhysicalFlags.bExplosionProof = false;
            otherVehicle->BlowUpCar (NULL, false);
        }

        if (playerVehicle == otherVehicle)
        {
            thisVehicle->m_nPhysicalFlags.bExplosionProof = false;
            thisVehicle->BlowUpCar (NULL, false);
        }
    }
};

DEFINE_EFFECT (SmashNBoomEffect, "effect_smash_n_boom", 0);