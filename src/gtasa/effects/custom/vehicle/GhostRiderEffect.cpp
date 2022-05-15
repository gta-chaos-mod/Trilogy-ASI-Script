#include "util/Config.h"
#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

class GhostRiderEffect : public EffectBase
{
    struct VehicleInfo
    {
        CVehicle *vehicle;
        int       time = 5000;
    };

    std::vector<VehicleInfo> vehicleList = {};
    CVehicle                *lastVehicle = nullptr;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        vehicleList.clear ();
        lastVehicle = nullptr;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (vehicleList.size () > 0)
        {
            for (auto &info : vehicleList)
            {
                if (IsVehiclePointerValid (info.vehicle))
                {
                    info.vehicle->m_nPhysicalFlags.bExplosionProof = false;
                    info.vehicle->BlowUpCar (NULL, false);
                }
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CountDownAndExplodeVehicles ();

        CVehicle *currentVehicle = FindPlayerVehicle (-1, false);

        if (currentVehicle && currentVehicle->IsDriver (FindPlayerPed ()))
        {
            RemoveVehicleIfExists (currentVehicle);

            SetBurnTimer (currentVehicle, 0.0f);
        }
        else if (!currentVehicle && lastVehicle
                 && !ContainsVehicle (lastVehicle))
        {
            vehicleList.push_back (VehicleInfo{.vehicle = lastVehicle});

            lastVehicle->m_fHealth = 1000.0f;
        }

        lastVehicle = currentVehicle;
    }

    bool
    ContainsVehicle (CVehicle *vehicle)
    {
        return std::find_if (vehicleList.begin (), vehicleList.end (),
                             [vehicle] (VehicleInfo info)
                             { return info.vehicle == vehicle; })
               != vehicleList.end ();
    }

    void
    RemoveVehicleIfExists (CVehicle *vehicle)
    {
        std::erase_if (vehicleList, [vehicle] (VehicleInfo &info)
                       { return info.vehicle == vehicle; });
    }

    void
    CountDownAndExplodeVehicles ()
    {
        int step = (int) GenericUtil::CalculateTick ();

        if (vehicleList.size () > 0)
        {
            for (auto &info : vehicleList)
            {
                CVehicle *vehicle = info.vehicle;
                if (vehicle)
                {
                    info.time -= step;
                    if (info.time < 0)
                    {
                        if (IsVehiclePointerValid (vehicle))
                        {
                            vehicle->m_nPhysicalFlags.bExplosionProof = false;
                            vehicle->BlowUpCar (NULL, false);
                        }
                    }
                }
            }

            std::erase_if (vehicleList,
                           [] (VehicleInfo &info) {
                               return !IsVehiclePointerValid (info.vehicle)
                                      || info.time < 0;
                           });
        }
    }

    void
    SetBurnTimer (CVehicle *vehicle, float value)
    {
        if (!vehicle || !CPools::ms_pVehiclePool->IsObjectValid (vehicle))
        {
            return;
        }

        CBaseModelInfo *model
            = CModelInfo::ms_modelInfoPtrs[vehicle->m_nModelIndex];
        if (!model) return;

        CVehicleModelInfo *vehicleModelInfo
            = reinterpret_cast<CVehicleModelInfo *> (model);
        if (!vehicleModelInfo) return;

        switch (vehicleModelInfo->m_nVehicleType)
        {
            case VEHICLE_BIKE:
            {
                CBike *bike     = (CBike *) vehicle;
                bike->m_fHealth = 249.0f;
                // bike->field_7BC = (int)value; // This should also be a
                // float, until then we use the float pointer
                *(float *) ((char *) vehicle + 1980) = value;
                break;
            }
            case VEHICLE_AUTOMOBILE:
            case VEHICLE_MTRUCK:
            case VEHICLE_QUAD:
            case VEHICLE_TRAILER:
            {
                CAutomobile *automobile = (CAutomobile *) vehicle;
                automobile->m_fHealth   = 249.0f;
                // automobile->m_dwBurnTimer = (int)value; // This should be
                // a float, until then we use the float pointer
                *(float *) ((char *) vehicle + 2276) = value;
                break;
            }
            case VEHICLE_BOAT:
            {
                CBoat *boat           = (CBoat *) vehicle;
                boat->m_fHealth       = 249.0f;
                boat->m_fBurningTimer = value;
                break;
            }
        }
    }
};

DEFINE_EFFECT (GhostRiderEffect, "effect_ghost_rider", 0);