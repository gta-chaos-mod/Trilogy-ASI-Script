#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class SendVehiclesToSpaceEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle && vehicle->m_nStatus != STATUS_WRECKED
                && vehicle->m_fHealth > 0.0f)
                return true;
        }

        return true;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_vecMoveSpeed.x += inst->Random (-2.5f, 2.5f);
            vehicle->m_vecMoveSpeed.y += inst->Random (-2.5f, 2.5f);
            vehicle->m_vecMoveSpeed.z += 10.0f;
        }
    }
};

DEFINE_EFFECT (SendVehiclesToSpaceEffect, "effect_send_vehicles_to_space", 0);