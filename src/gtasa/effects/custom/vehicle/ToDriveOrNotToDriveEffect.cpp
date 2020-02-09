#include "ToDriveOrNotToDriveEffect.h"

ToDriveOrNotToDriveEffect::ToDriveOrNotToDriveEffect ()
    : EffectBase ("effect_to_drive_or_not_to_drive")
{
}

void
ToDriveOrNotToDriveEffect::Disable ()
{
    FixTires ();

    EffectBase::Disable ();
}

void
ToDriveOrNotToDriveEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (wait > 0)
    {
        wait -= CalculateTick ();
        return;
    }

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
        wait = Random (2000, 5000);
    }
}

void
ToDriveOrNotToDriveEffect::FixTires ()
{
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
        {
            CBike *bike                   = reinterpret_cast<CBike *> (vehicle);
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

void
ToDriveOrNotToDriveEffect::PopTires ()
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
