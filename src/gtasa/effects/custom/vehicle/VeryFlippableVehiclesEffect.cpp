#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <cHandlingDataMgr.h>

class VeryFlippableVehiclesEffect : public EffectBase
{
    tHandlingData origVehicleHandling[210] = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int i = 0; i < 210; i++)
        {
            origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];

            if (origVehicleHandling[i].m_bIsBike) continue;

            gHandlingDataMgr.m_aVehicleHandling[i].m_vecCentreOfMass.z = 2.0f;
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (int i = 0; i < 210; i++)
        {
            gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();
    }
};

DEFINE_EFFECT (VeryFlippableVehiclesEffect, "effect_very_flippable_vehicles",
               GROUP_HANDLING);