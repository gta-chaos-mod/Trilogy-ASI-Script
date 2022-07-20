#include "util/EffectBase.h"

class ForceFieldEffect : public EffectBase
{
    const float startDistance    = 15.0f;
    const float maxForceDistance = 10.0f;
    const float maxForce         = 50.0f;

public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector playerPos = player->GetPosition ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player || !IsPedPointerValid (ped)) continue;

            MovePhysical (ped, playerPos);
        }

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle == playerVehicle || !IsVehiclePointerValid (vehicle))
                continue;

            MovePhysical (vehicle, playerPos);
        }
    }

    void
    MovePhysical (CPhysical *physical, CVector playerPos)
    {
        CVector physicalPos = physical->GetPosition ();
        float   distance    = DistanceBetweenPoints (playerPos, physicalPos);

        if (distance > startDistance) return;

        physical->m_nPhysicalFlags.bApplyGravity     = true;
        physical->m_nPhysicalFlags.bDisableMoveForce = false;
        physical->m_nPhysicalFlags.bDisableZ         = false;

        float forceDistance
            = std::min (std::max (0.0f, (startDistance - distance)),
                        maxForceDistance);
        float force = forceDistance / maxForceDistance * maxForce;

        CVector difference = physicalPos - playerPos;
        if (physical->m_nType == ENTITY_TYPE_PED) difference.z += 0.5f;

        physical->ApplyMoveForce (difference * force);
    }
};

DEFINE_EFFECT (ForceFieldEffect, "effect_force_field", 0);