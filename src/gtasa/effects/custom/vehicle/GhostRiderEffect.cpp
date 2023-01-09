#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

// Car on "Wear Flowers In Your Hair" and the Tankers in trucking missions blow
// up immediately
class GhostRiderEffect : public EffectBase
{
    struct VehicleInfo
    {
        CVehicle *vehicle;
        int       time = 5000;
    };

    std::vector<VehicleInfo> vehicleList = {};
    CVehicle                *lastVehicle = nullptr;

    static inline bool specialMissionsFix = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        specialMissionsFix = false;

        vehicleList.clear ();
        lastVehicle = nullptr;

        HOOK_METHOD_ARGS (inst, Hooked_0x495_IsCarOnFire_CollectParameters,
                          __int16 (CRunningScript *, unsigned __int16),
                          0x48AF37);

        HOOK_METHOD_ARGS (inst, Hooked_0x495_IsCarOnFire_UpdateCompareFlag,
                          unsigned __int16 (CRunningScript *, char), 0x48B351,
                          0x48AFA7);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (!vehicleList.size ()) return;

        for (auto &info : vehicleList)
        {
            if (IsVehiclePointerValid (info.vehicle))
            {
                info.vehicle->m_nPhysicalFlags.bExplosionProof = false;
                info.vehicle->BlowUpCar (nullptr, false);
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

        if (!vehicleList.size ()) return;

        for (auto &info : vehicleList)
        {
            CVehicle *vehicle = info.vehicle;
            if (!vehicle) continue;

            info.time -= step;
            if (info.time > 0) continue;

            if (!IsVehiclePointerValid (vehicle)) continue;

            vehicle->m_nPhysicalFlags.bExplosionProof = false;
            vehicle->BlowUpCar (nullptr, false);
        }

        std::erase_if (vehicleList,
                       [] (VehicleInfo &info) {
                           return !IsVehiclePointerValid (info.vehicle)
                                  || info.time < 0;
                       });
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
                CBike *bike           = (CBike *) vehicle;
                bike->m_fHealth       = 249.0f;
                bike->m_fBurningTimer = value;
                break;
            }
            case VEHICLE_AUTOMOBILE:
            case VEHICLE_MTRUCK:
            case VEHICLE_QUAD:
            case VEHICLE_TRAILER:
            {
                CAutomobile *automobile     = (CAutomobile *) vehicle;
                automobile->m_fHealth       = 249.0f;
                automobile->m_fBurningTimer = value;
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

        if (vehicle->m_pTrailer && IsVehiclePointerValid (vehicle->m_pTrailer))
        {
            SetBurnTimer (vehicle->m_pTrailer, value);
        }
    }

    static __int16
    Hooked_0x495_IsCarOnFire_CollectParameters (auto           &&cb,
                                                CRunningScript  *thisScript,
                                                unsigned __int16 a2)
    {
        __int16 result = cb ();

        std::string missionName
            = GenericUtil::ToUpper (std::string (thisScript->m_szName));
        if (missionName == "SWEET3" || missionName == "GARAG1")
            specialMissionsFix = true;

        return result;
    }

    static unsigned __int16
    Hooked_0x495_IsCarOnFire_UpdateCompareFlag (auto          &&cb,
                                                CRunningScript *thisScript,
                                                char           &flag)
    {
        if (specialMissionsFix)
        {
            specialMissionsFix = false;
            flag               = false;
        }

        return cb ();
    }
};

DEFINE_EFFECT (GhostRiderEffect, "effect_ghost_rider", 0);