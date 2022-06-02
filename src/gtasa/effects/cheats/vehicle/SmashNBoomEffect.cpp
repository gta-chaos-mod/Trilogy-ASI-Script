#include "util/EffectBase.h"

using namespace plugin;

class SmashNBoomEffect : public EffectBase
{
    static inline ThiscallEvent<
        AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL,
                    0x54C435, H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL,
                    0x54D3FE, H_CALL, 0x54D4D2, H_CALL>,
        PRIORITY_AFTER,
        ArgPick<ArgTypes<CPhysical *, CPhysical *, int, float *, int>, 0, 1, 2,
                3, 4>,
        void (CPhysical *, CPhysical *, int, float *, int)>
        applyCollisionEvent;

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
    ApplyCollision (CPhysical *thisEntity, CPhysical *otherEntity, int a3,
                    float *a4, int a5)
    {
        if (thisEntity->m_nType != ENTITY_TYPE_VEHICLE
            || otherEntity->m_nType != ENTITY_TYPE_VEHICLE)
        {
            return;
        }

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (!playerVehicle) return;

        if (playerVehicle == thisEntity)
        {
            otherEntity->m_nPhysicalFlags.bExplosionProof = false;
            ((CVehicle *) otherEntity)->BlowUpCar (nullptr, false);
        }

        if (playerVehicle == otherEntity)
        {
            thisEntity->m_nPhysicalFlags.bExplosionProof = false;
            ((CVehicle *) thisEntity)->BlowUpCar (nullptr, false);
        }
    }
};

DEFINE_EFFECT (SmashNBoomEffect, "effect_smash_n_boom", 0);