#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

class SendVehiclesToSpaceEffect : public OneTimeEffect
{
public:
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