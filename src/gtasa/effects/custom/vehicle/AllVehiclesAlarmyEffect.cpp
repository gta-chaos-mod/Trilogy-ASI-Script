#include "util/EffectBase.h"
#include "util/GameUtil.h"

class AllVehiclesAlarmyEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_nAlarmState == 0
                && vehicle->m_pDriver != FindPlayerPed ())
                vehicle->m_nAlarmState = USHRT_MAX;
        }
    }
};

DEFINE_EFFECT (AllVehiclesAlarmyEffect, "effect_all_vehicles_alarmy", 0);