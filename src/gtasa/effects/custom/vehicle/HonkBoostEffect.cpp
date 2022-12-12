#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"

class HonkBoostEffect : public EffectBase
{
    std::map<CVehicle *, bool> wasHornOn;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wasHornOn.clear ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_nHornCounter > 0)
            {
                wasHornOn[vehicle] = true;

                ApplyVehicleSpeed (vehicle, 1.5f);
            }
            else if (wasHornOn[vehicle])
            {
                wasHornOn[vehicle] = false;

                ApplyVehicleSpeed (vehicle, 0.75f);
            }
        }
    }

    void
    ApplyVehicleSpeed (CVehicle *vehicle, float velocity)
    {
        // Don't apply for empty vehicles or mission ped drivers
        CPed *driver = vehicle->m_pDriver;

        if (!driver) return;
        if (driver->m_nCreatedBy == 2 && driver != FindPlayerPed ()) return;

        CMatrixLink *matrix = vehicle->GetMatrix ();

        vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
        vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
        vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;

        vehicle->m_pDriver->m_nPedFlags.CantBeKnockedOffBike = false;
    }
};

DEFINE_EFFECT (HonkBoostEffect, "effect_honk_boost", 0);