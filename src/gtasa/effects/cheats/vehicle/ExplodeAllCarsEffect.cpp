#include "util/EffectBase.h"
#include "util/GameUtil.h"

class ExplodeAllCarsEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bExplosionProof = false;
            vehicle->BlowUpCar (nullptr, false);
        }

        inst->Disable ();
    }
};

DEFINE_EFFECT (ExplodeAllCarsEffect, "effect_explode_all_cars", 0);