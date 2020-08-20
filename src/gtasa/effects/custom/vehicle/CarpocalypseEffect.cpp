#include "CarpocalypseEffect.h"
#include "CPopulation.h"
#include "CStreaming.h"

CarpocalypseEffect::CarpocalypseEffect ()
    : EffectBase ("effect_carpocalypse")
{
}

void
CarpocalypseEffect::RemoveExplodedVehicles (int step)
{
    const int DESPAWN_TIME = 5000;

    for (auto it = vehicleList.begin (); it != vehicleList.end (); ++it)
    {
        CVehicle *vehicle = it->first;
        int &     time    = it->second;

        if (vehicle->m_fHealth <= 0.0f)
            time += step;

        if (time > DESPAWN_TIME)
        {
            if (CPools::ms_pVehiclePool->IsObjectValid (vehicle))
                vehicle->m_nVehicleFlags.bFadeOut = true;

            it = vehicleList.erase (it);
        }
    }
}

float
CarpocalypseEffect::GetSpawnDistance ()
{
    float spawnDistance = 25.0f;

    CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
    if (playerVehicle)
        spawnDistance += playerVehicle->m_vecMoveSpeed.Magnitude2D () * 10.0f;

    return spawnDistance;
}

void
CarpocalypseEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    int step = CalculateTick ();

    // Make sure we delete vehicles after they've exploded
    RemoveExplodedVehicles (step);

    if (wait > 0)
    {
        wait -= step;
        return;
    }

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        CVector spawnPosition = player->GetPosition ();

        // Spawn a vehicle at a specified distance and a random angle from the
        // player
        float spawnDistance = GetSpawnDistance ();
        float thats_rad
            = GameUtil::ToRadians (RandomHelper::Random (0.0f, 360.0f));
        spawnPosition += CVector (spawnDistance * sin (thats_rad),
                                  spawnDistance * cos (thats_rad), 100.0f);

        for (int i = 0; i < RandomHelper::Random (1, 3); i++)
        {
            int carToSpawn = RandomHelper::Random (400, 611);

            // If too many vehicles are loaded, choose an already loaded
            // vehicle. Game limit is 22.
            int loadedVehicles = CStreaming::ms_vehiclesLoaded.CountMembers ();
            if (loadedVehicles > 20)
                carToSpawn = CStreaming::ms_vehiclesLoaded.GetMember (
                    RandomHelper::Random (0, loadedVehicles - 1));

            // If too many vehicles are in the pool, don't spawn any more
            // vehicles until there's room.
            if (CPools::ms_pVehiclePool->GetNoOfFreeSpaces () < 5
                || carToSpawn == -1)
                return;

            CVehicle *vehicle
                = GameUtil::CreateVehicle (carToSpawn, spawnPosition, 0.0f,
                                           false);

            if (vehicle)
            {
                vehicle->m_vecMoveSpeed.z -= 2.5f;
                vehicle->m_fHealth = 249.0f;

                vehicleList[vehicle] = 0;
            }
        }
    }

    wait = Random (500, 1000);
}
