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

                CMatrix *matrix   = vehicle->GetMatrix ();
                float    velocity = 1.5f;

                vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
                vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
                vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;

                if (vehicle->m_pDriver)
                    vehicle->m_pDriver->m_nPedFlags.CantBeKnockedOffBike = true;
            }
            else if (wasHornOn[vehicle])
            {
                wasHornOn[vehicle] = false;

                CMatrixLink *matrix   = vehicle->GetMatrix ();
                float        velocity = 0.75f;

                vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
                vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
                vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;

                if (vehicle->m_pDriver)
                    vehicle->m_pDriver->m_nPedFlags.CantBeKnockedOffBike
                        = false;
            }
        }
    }
};

DEFINE_EFFECT (HonkBoostEffect, "effect_honk_boost", 0);