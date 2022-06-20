#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

class ToDriveOrNotToDriveEffect : public EffectBase
{
    int  wait  = 0;
    bool doPop = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait  = 0;
        doPop = true;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        FixTires ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        GameUtil::SetVehiclesToRealPhysics ();

        doPop = !doPop;
        if (doPop)
        {
            PopTires ();
            wait = 500;
        }
        else
        {
            FixTires ();
            wait = inst->Random (1000 * 2, 1000 * 5);
        }
    }

    void
    PopTires ()
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bBulletProof   = false;
            vehicle->m_nVehicleFlags.bTyresDontBurst = false;

            vehicle->BurstTyre (eWheels::WHEEL_FRONT_LEFT, true);
            vehicle->BurstTyre (eWheels::WHEEL_REAR_LEFT, true);
            vehicle->BurstTyre (eWheels::WHEEL_REAR_RIGHT, true);
        }
    }

    void
    FixTires ()
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
            {
                CBike *bike = reinterpret_cast<CBike *> (vehicle);
                bike->m_anWheelDamageState[0] = 0;
                bike->m_anWheelDamageState[1] = 0;
            }
            else if (vehicle->m_nVehicleClass == VEHICLE_AUTOMOBILE)
            {
                CAutomobile *car = reinterpret_cast<CAutomobile *> (vehicle);
                car->FixTyre (eWheels::WHEEL_FRONT_LEFT);
                car->FixTyre (eWheels::WHEEL_REAR_LEFT);
                car->FixTyre (eWheels::WHEEL_FRONT_RIGHT);
                car->FixTyre (eWheels::WHEEL_REAR_RIGHT);
            }
        }
    }
};

DEFINE_EFFECT (ToDriveOrNotToDriveEffect, "effect_to_drive_or_not_to_drive", 0);