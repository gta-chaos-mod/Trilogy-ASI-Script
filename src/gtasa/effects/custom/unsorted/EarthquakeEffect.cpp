#include "util/EffectBase.h"

class EarthquakeEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (inst->Random (0, 10) != 0) continue;

            vehicle->m_vecMoveSpeed.x += inst->Random (-0.1f, 0.1f, 0.25f);
            vehicle->m_vecMoveSpeed.y += inst->Random (-0.1f, 0.1f, 0.25f);
            vehicle->m_vecMoveSpeed.z += inst->Random (-0.1f, 0.1f);

            if (inst->Random (0, 10) != 0) continue;

            vehicle->m_vecTurnSpeed.x += inst->Random (-0.1f, 0.1f, 0.25f);
            vehicle->m_vecTurnSpeed.y += inst->Random (-0.1f, 0.1f, 0.25f);
            vehicle->m_vecTurnSpeed.z += inst->Random (-0.1f, 0.1f, 0.25f);
        }
    }
};

DEFINE_EFFECT (EarthquakeEffect, "effect_earthquake", 0);