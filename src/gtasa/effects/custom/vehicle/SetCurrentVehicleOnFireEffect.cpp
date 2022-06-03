#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class SetCurrentVehicleOnFireEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return;

        vehicle->m_nPhysicalFlags.bFireProof = false;
        vehicle->m_fHealth                   = 249.9f;
    }
};

DEFINE_EFFECT (SetCurrentVehicleOnFireEffect,
               "effect_set_current_vehicle_on_fire", 0);