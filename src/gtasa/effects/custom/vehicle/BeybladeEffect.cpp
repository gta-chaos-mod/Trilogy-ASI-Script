#include "util/EffectBase.h"
#include "util/GameUtil.h"

class BeybladeEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            vehicle->m_vecTurnSpeed.z = 1.5f;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_pDriver && vehicle->m_pDriver != FindPlayerPed ()
                && vehicle->m_nCreatedBy != 2)
            {
                vehicle->m_vecTurnSpeed.z = 1.5f;
                vehicle->m_fHealth        = 1000.0f;
            }
        }
    }
};

DEFINE_EFFECT (BeybladeEffect, "effect_beyblade", 0);