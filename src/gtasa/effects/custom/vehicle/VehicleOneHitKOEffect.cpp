#include "util/Config.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

using namespace plugin;

class VehicleOneHitKOEffect : public EffectBase
{
    static inline std::map<CVehicle *, float> vehicleHealthMap = {};

    bool shouldExplode = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        shouldExplode
            = Config::GetOrDefault ("Effects.VehicleOneHitKO_ExplodeVehicles",
                                    true);

        vehicleHealthMap.clear ();

        for (auto vehicle : CPools::ms_pVehiclePool)
        {
            vehicleHealthMap[vehicle] = vehicle->m_fHealth;
        }

        Events::vehicleCtorEvent += OnVehicleCreated;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (auto vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicleHealthMap.contains (vehicle)
                && vehicle->m_fHealth < vehicleHealthMap[vehicle])
            {
                if (shouldExplode)
                {
                    vehicle->m_nPhysicalFlags.bExplosionProof = false;
                    vehicle->BlowUpCar (NULL, false);
                }
                else
                {
                    vehicle->m_fHealth = 0.0f;
                }
                vehicleHealthMap.erase (vehicle);
            }
        }
    }

    static void
    OnVehicleCreated (CVehicle *vehicle)
    {
        vehicleHealthMap[vehicle] = vehicle->m_fHealth;
    }
};

DEFINE_EFFECT (VehicleOneHitKOEffect, "effect_vehicle_one_hit_ko", 0);