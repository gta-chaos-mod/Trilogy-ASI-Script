#include "util/Config.h"
#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

class ToTheLeftToTheRightEffect : public EffectBase
{
    int wait = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait = 0;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (!Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            {
                float amplify = 10.0f;

                vehicle->m_vecMoveSpeed.x
                    += inst->Random (-0.25f, 0.25f, amplify);
                vehicle->m_vecMoveSpeed.y
                    += inst->Random (-0.25f, 0.25f, amplify);
                vehicle->m_vecMoveSpeed.z
                    += inst->Random (-0.05f, 0.05f, amplify);
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            float amplify = 2.0f;
            if (inst->Random (0, 19) == 0) { amplify = 10.0f; }

            vehicle->m_vecMoveSpeed.x += inst->Random (-0.25f, 0.25f, amplify);
            vehicle->m_vecMoveSpeed.y += inst->Random (-0.25f, 0.25f, amplify);
            vehicle->m_vecMoveSpeed.z += inst->Random (-0.05f, 0.05f, amplify);
        }

        wait = inst->Random (5000, 10000);
    }
};

DEFINE_EFFECT (ToTheLeftToTheRightEffect, "effect_to_the_left_to_the_right", 0);