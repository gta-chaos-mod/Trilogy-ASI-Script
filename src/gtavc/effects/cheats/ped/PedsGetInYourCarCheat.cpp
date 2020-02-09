#include "PedsGetInYourCarCheat.h"

PedsGetInYourCarCheat::PedsGetInYourCarCheat ()
    : EffectPlaceholder ("cheat_peds_get_in_your_car")
{
}

void
PedsGetInYourCarCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CVehicle *vehicle = FindPlayerVehicle ();
    if (vehicle && (!vehicle->m_nVehicleClass || vehicle->m_nVehicleClass == 5))
    {
        if (vehicle->m_nVehicleClass == 5)
        {
            if (vehicle->m_passengers[0])
            {
                vehicle->m_passengers[0]->SetObjective (
                    eObjective::OBJECTIVE_LEAVE_CAR, vehicle);
            }
        }

        CPlayerPed *player = FindPlayerPed ();
        CEntity *   entity
            = CWorld::TestSphereAgainstWorld (vehicle->GetPosition (),
                                              0x40C00000, player, false, false,
                                              true, false, false, false);

        if (entity && entity->m_nType != 50)
        {
            ((CPed *) entity)
                ->SetObjective (eObjective::OBJECTIVE_ENTER_CAR_AS_PASSENGER,
                                vehicle);
        }
    }
}
