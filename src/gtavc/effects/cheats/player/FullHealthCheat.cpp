#include "FullHealthCheat.h"

FullHealthCheat::FullHealthCheat () : EffectPlaceholder ("cheat_full_health") {}

void
FullHealthCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *ped = FindPlayerPed ();
    if (ped)
    {
        ped->m_fHealth = 100.0f;
    }

    CVehicle *vehicle = FindPlayerVehicle ();
    if (vehicle)
    {
        float setHealth    = vehicle->m_fHealth > 1000.0f ? 100000.0f : 1000.0f;
        vehicle->m_fHealth = setHealth;
        if (!vehicle->m_nVehicleClass)
        {
            CAutomobile *car = (CAutomobile *) vehicle;

            car->m_carDamage.SetEngineStatus (0);

            car->m_carDamage.SetWheelStatus (0, 0);
            car->m_carDamage.SetWheelStatus (1, 0);
            car->m_carDamage.SetWheelStatus (2, 0);
            car->m_carDamage.SetWheelStatus (3, 0);
        }
    }
}
