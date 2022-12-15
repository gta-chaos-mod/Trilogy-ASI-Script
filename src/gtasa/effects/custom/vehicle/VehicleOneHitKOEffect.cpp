#include "util/Config.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

class VehicleOneHitKOEffect : public EffectBase
{
    static inline std::map<CVehicle *, float> vehicleHealthMap = {};

    bool shouldExplode = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        shouldExplode
            = CONFIG ("Effects.VehicleOneHitKO.ExplodeVehicles", false);

        vehicleHealthMap.clear ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (auto vehicle : CPools::ms_pVehiclePool)
        {
            if (!vehicleHealthMap.contains (vehicle)
                && vehicle->m_nStatus != STATUS_WRECKED
                && vehicle->CanBeDriven () && vehicle->m_fHealth > 0.0f)
            {
                vehicleHealthMap[vehicle] = vehicle->m_fHealth;
            }

            if (vehicleHealthMap.contains (vehicle)
                && vehicle->m_fHealth < vehicleHealthMap[vehicle])
            {
                if (shouldExplode)
                {
                    vehicle->m_nPhysicalFlags.bExplosionProof = false;
                    vehicle->BlowUpCar (nullptr, false);
                }
                else
                {
                    vehicle->m_fHealth = 0.0f;
                }

                vehicleHealthMap.erase (vehicle);
            }
        }
    }
};

DEFINE_EFFECT (VehicleOneHitKOEffect, "effect_vehicle_one_hit_ko", 0);