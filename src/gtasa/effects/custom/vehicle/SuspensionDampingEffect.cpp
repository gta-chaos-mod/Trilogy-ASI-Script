#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include "cHandlingDataMgr.h"

class SuspensionDampingEffect : public EffectBase
{
    tHandlingData origVehicleHandling[210] = {};
    float         suspension               = 1.0f;

public:
    SuspensionDampingEffect (float suspension) : EffectBase ()
    {
        this->suspension = suspension;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        for (int i = 0; i < 210; i++)
        {
            this->origVehicleHandling[i]
                = gHandlingDataMgr.m_aVehicleHandling[i];

            gHandlingDataMgr.m_aVehicleHandling[i].m_fSuspensionDampingLevel
                = this->suspension;
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (int i = 0; i < 210; i++)
        {
            gHandlingDataMgr.m_aVehicleHandling[i]
                = this->origVehicleHandling[i];
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();
    }
};

// clang-format off
DEFINE_EFFECT (SuspensionDampingEffect, "effect_high_suspension_damping", GROUP_HANDLING, 10.0f);
DEFINE_EFFECT (SuspensionDampingEffect, "effect_zero_suspension_damping", GROUP_HANDLING, -1.0f);
// clang-format on