#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

class SetCurrentVehicleOnFireEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            playerVehicle->m_nPhysicalFlags.bFireProof = false;
            playerVehicle->m_fHealth                   = 249.9f;
        }
    }
};

DEFINE_EFFECT (SetCurrentVehicleOnFireEffect,
               "effect_set_current_vehicle_on_fire", 0);