#include "PopTiresOfAllVehiclesEffect.h"

PopTiresOfAllVehiclesEffect::PopTiresOfAllVehiclesEffect ()
    : EffectBase ("effect_pop_tires_of_all_vehicles")
{
}

void
PopTiresOfAllVehiclesEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    // Make sure to check against the popped tires so we don't do it too often
    // Only once.

    GameUtil::SetVehiclesToRealPhysics ();

    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        vehicle->m_nPhysicalFlags.bBulletProof   = false;
        vehicle->m_nVehicleFlags.bTyresDontBurst = false;

        if (CModelInfo::IsCarModel (vehicle->m_nModelIndex))
        {
            CAutomobile *car = (CAutomobile *) vehicle;

            if (!car->m_damageManager.GetWheelStatus (
                    eWheels::WHEEL_FRONT_LEFT))
            {
                vehicle->BurstTyre (eWheels::WHEEL_FRONT_LEFT, false);
            }

            if (!car->m_damageManager.GetWheelStatus (eWheels::WHEEL_REAR_LEFT))
            {
                vehicle->BurstTyre (eWheels::WHEEL_REAR_LEFT, false);
            }

            if (!car->m_damageManager.GetWheelStatus (
                    eWheels::WHEEL_REAR_RIGHT))
            {
                vehicle->BurstTyre (eWheels::WHEEL_REAR_RIGHT, false);
            }
        }
        else if (CModelInfo::IsBikeModel (vehicle->m_nModelIndex))
        {
            CBike *bike = (CBike *) vehicle;

            if (!bike->m_anWheelDamageState[0])
            {
                vehicle->BurstTyre (eWheels::WHEEL_FRONT_LEFT, false);
            }

            if (!bike->m_anWheelDamageState[1])
            {
                vehicle->BurstTyre (eWheels::WHEEL_REAR_LEFT, false);
            }
        }
    }
}
