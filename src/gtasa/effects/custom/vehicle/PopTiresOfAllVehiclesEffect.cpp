#include <util/EffectBase.h>
#include <util/GameUtil.h>

class PopTiresOfAllVehiclesEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bBulletProof   = false;
            vehicle->m_nVehicleFlags.bTyresDontBurst = false;

            if (vehicle->m_nVehicleClass == VEHICLE_AUTOMOBILE
                || vehicle->m_nVehicleClass == VEHICLE_QUAD)
            {
                CAutomobile *car = (CAutomobile *) vehicle;

                if (!car->m_damageManager.GetWheelStatus (
                        eWheels::WHEEL_FRONT_LEFT))
                {
                    vehicle->BurstTyre (eWheels::WHEEL_FRONT_LEFT, false);
                }

                if (!car->m_damageManager.GetWheelStatus (
                        eWheels::WHEEL_REAR_LEFT))
                {
                    vehicle->BurstTyre (eWheels::WHEEL_REAR_LEFT, false);
                }

                if (!car->m_damageManager.GetWheelStatus (
                        eWheels::WHEEL_REAR_RIGHT))
                {
                    vehicle->BurstTyre (eWheels::WHEEL_REAR_RIGHT, false);
                }
            }
            else if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
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
};

DEFINE_EFFECT (PopTiresOfAllVehiclesEffect, "effect_pop_tires_of_all_vehicles",
               0);