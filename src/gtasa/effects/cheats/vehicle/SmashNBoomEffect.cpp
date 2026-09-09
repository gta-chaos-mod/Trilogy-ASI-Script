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
            if (!vehicle) continue;

            vehicle->bInvulnerable   = false;
            vehicle->bExplosionProof = false;
            vehicle->bFireProof      = false;
            vehicle->bCollisionProof = false;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player        = FindPlayerPed ();
        CVehicle   *playerVehicle = FindPlayerVehicle (-1, false);

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (!vehicle) continue;

            bool proof               = (player && playerVehicle == vehicle
                                        && playerVehicle->IsDriver (player));
            vehicle->bInvulnerable   = proof;
            vehicle->bExplosionProof = proof;
            vehicle->bFireProof      = proof;
            vehicle->bCollisionProof = proof;
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
            otherEntity->bExplosionProof = false;
            ((CVehicle *) otherEntity)->BlowUpCar (nullptr, false);
        }

        if (playerVehicle == otherEntity)
        {
            thisEntity->bExplosionProof = false;
            ((CVehicle *) thisEntity)->BlowUpCar (nullptr, false);
        }
    }
};

DEFINE_EFFECT (SmashNBoomEffect, "effect_smash_n_boom", 0);