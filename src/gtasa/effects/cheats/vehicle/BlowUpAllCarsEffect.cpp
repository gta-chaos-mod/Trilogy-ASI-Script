#include <util/EffectBase.h>
#include <util/GameUtil.h>

class BlowUpAllCarsEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        if (CanBlowUpCars ())
        {
            for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            {
                vehicle->m_nPhysicalFlags.bExplosionProof = false;
                vehicle->BlowUpCar (NULL, false);
            }

            inst->Disable ();
        }
    }

    bool
    CanBlowUpCars ()
    {
        return GameUtil::IsPlayerSafe ();
    }
};

DEFINE_EFFECT (BlowUpAllCarsEffect, "effect_blow_up_all_cars", 0);