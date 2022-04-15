#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/MathHelper.h>

using namespace plugin;

class HonkBoostEffect : public EffectBase
{
    std::map<CVehicle *, bool> wasHornOn;

public:
    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_nHornCounter > 0)
            {
                wasHornOn[vehicle] = true;

                CMatrixLink *matrix   = vehicle->GetMatrix ();
                float        velocity = 1.5f;

                vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
                vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
                vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;
            }
            else if (wasHornOn[vehicle])
            {
                wasHornOn[vehicle] = false;

                CMatrixLink *matrix   = vehicle->GetMatrix ();
                float        velocity = 0.75f;

                vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
                vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
                vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;
            }
        }
    }
};

DEFINE_EFFECT (HonkBoostEffect, "effect_honk_boost", 0);