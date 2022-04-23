#include <util/Config.h>
#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/GenericUtil.h>

class GhostRiderEffect : public EffectBase
{
    std::map<CVehicle *, int> vehicleList = {};
    CVehicle                 *lastVehicle = nullptr;

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
        if (Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                vehicle->m_nPhysicalFlags.bExplosionProof = false;
                vehicle->BlowUpCar (NULL, false);
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        int step = (int) GenericUtil::CalculateTick ();

        if (this->vehicleList.size () > 0)
        {
            for (auto it = this->vehicleList.begin ();
                 it != this->vehicleList.end (); ++it)
            {
                CVehicle *vehicle = it->first;

                if (vehicle)
                {
                    this->vehicleList[vehicle] -= step;
                    if (this->vehicleList[vehicle] < 0)
                    {
                        if (CPools::ms_pVehiclePool->IsObjectValid (vehicle))
                        {
                            vehicle->m_nPhysicalFlags.bExplosionProof = false;
                            vehicle->BlowUpCar (NULL, false);
                        }
                        it = this->vehicleList.erase (it);
                    }
                }
                else
                {
                    it = this->vehicleList.erase (it);
                }
            }
        }

        CVehicle *currentVehicle = FindPlayerVehicle (-1, false);

        if (currentVehicle && currentVehicle->IsDriver (FindPlayerPed ()))
        {
            if (this->vehicleList.contains (currentVehicle))
            {
                auto it = this->vehicleList.find (currentVehicle);
                if (it != this->vehicleList.end ())
                {
                    it = this->vehicleList.erase (it);
                }
            }

            SetBurnTimer (currentVehicle, 0.0f);
        }
        else if (!currentVehicle && this->lastVehicle
                 && !this->vehicleList.contains (this->lastVehicle))
        {
            this->vehicleList[this->lastVehicle] = 5000;
            this->lastVehicle->m_fHealth         = 1000.0f;
        }

        this->lastVehicle = currentVehicle;
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
                // bike->field_7BC = (int)value; // This should also be a float,
                // until then we use the float pointer
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
                // automobile->m_dwBurnTimer = (int)value; // This should be a
                // float, until then we use the float pointer
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