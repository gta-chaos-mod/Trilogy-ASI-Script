#include "VehicularRainEffect.h"

VehicularRainEffect::VehicularRainEffect ()
    : EffectBase ("effect_vehicular_rain")
{
}

void
VehicularRainEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    // Make sure we delete vehicles after they've exploded
    int step = CalculateTick ();

    if (vehicleList.size () > 0)
    {
        for (auto it = vehicleList.begin (); it != vehicleList.end (); ++it)
        {
            CVehicle *vehicle = it->first;

            if (vehicle)
            {
                if (vehicle->m_fHealth == 0.0f && vehicleList[vehicle] == -1)
                {
                    vehicleList[vehicle] = 5000;
                }
                else if (vehicleList[vehicle] > 0)
                {
                    vehicleList[vehicle] -= step;
                    if (vehicleList[vehicle] < 0)
                    {
                        if (CPools::ms_pVehiclePool->IsObjectValid (vehicle))
                        {
                            vehicle->m_nPhysicalFlags.bExplosionProof = false;
                            CCarCtrl::PossiblyRemoveVehicle (vehicle);
                        }
                        it = vehicleList.erase (it);
                    }
                }
            }
            else
            {
                it = vehicleList.erase (it);
            }
        }
    }

    if (wait > 0)
    {
        wait -= CalculateTick ();
        return;
    }

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        CVector spawnPosition = player->GetPosition ();

        float thats_rad
            = GameUtil::ToRadians (RandomHelper::Random (0.0f, 360.0f));
        spawnPosition
            += CVector (25.0f * sin (thats_rad), 25.0f * cos (thats_rad), 100.0f);

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            spawnPosition -= (playerVehicle->m_vecMoveSpeed * 5);
        }

        for (int i = 0; i < RandomHelper::Random (1, 3); i++)
        {
            CVehicle *vehicle
                = GameUtil::CreateVehicle (RandomHelper::Random (400, 611),
                                           spawnPosition, 0.0f, false);
            vehicle->m_vecMoveSpeed.z -= 2.5f;
            vehicle->m_fHealth = 250.0f;

            vehicleList[vehicle] = -1;
        }
    }

    wait = Random (500, 1000);
}
