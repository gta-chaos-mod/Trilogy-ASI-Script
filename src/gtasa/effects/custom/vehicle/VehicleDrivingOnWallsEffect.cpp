#include <util/EffectBase.h>

#include "CTimer.h"

class VehicleDrivingOnWallsEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            NegateGravity (vehicle);
            ApplyRelativeGravity (vehicle);
        }
    }

    void
    NegateGravity (CPhysical *physical)
    {
        float gravity = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;
        physical->ApplyMoveForce ({0, 0, -gravity});
    }

    void
    ApplyRelativeGravity (CPhysical *physical)
    {
        float gravity = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;

        CMatrixLink *matrix = physical->GetMatrix ();
        physical->ApplyMoveForce ({matrix->at.x * gravity,
                                   matrix->at.y * gravity,
                                   matrix->at.z * gravity});
    }
};

DEFINE_EFFECT (VehicleDrivingOnWallsEffect, "effect_vehicle_driving_on_walls",
               0);
