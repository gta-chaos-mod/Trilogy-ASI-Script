#include "CarmageddonEffect.h"
#include "CPopulation.h"
#include "CStreaming.h"

CarmageddonEffect::CarmageddonEffect () : EffectBase ("effect_carmageddon") {}

void
CarmageddonEffect::RemoveExplodedVehicles (int step)
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
CarmageddonEffect::GetSpawnDistance ()
{
    float spawnDistance = 0.0f;

    CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
    if (playerVehicle)
        spawnDistance += playerVehicle->m_vecMoveSpeed.Magnitude2D () * 4.2f;

    return spawnDistance;
}

void
CarmageddonEffect::HandleTick ()
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
        // Spawn a vehicle at a specified distance and a random angle from the
        // player
        float   spawnDistance = GetSpawnDistance ();
        CVector spawnPosition = player->TransformFromObjectSpace (
            CVector (0.0f, spawnDistance, 50.0f));

        float thats_rad
            = GameUtil::ToRadians (RandomHelper::Random (0.0f, 360.0f));

        spawnPosition
            += CVector (30.0f * sin (thats_rad), 30.0f * cos (thats_rad), 0.0f);

        for (int i = 0; i < RandomHelper::Random (1, 3); i++)
        {
            int carToSpawn = possibleVehicles[RandomHelper::Random (
                0, possibleVehicles.size () - 1)];

            // If too many vehicles are loaded, choose an already loaded
            // vehicle. Game limit is 22.
            int loadedVehicles = CStreaming::ms_vehiclesLoaded.CountMembers ();
            if (loadedVehicles > 20)
                carToSpawn = CStreaming::ms_vehiclesLoaded.GetMember (
                    RandomHelper::Random (0, loadedVehicles - 1));

            // Non valid vehicle
            if (std::find (possibleVehicles.begin (), possibleVehicles.end (),
                           carToSpawn)
                == possibleVehicles.end ())
            {
                i--;
                return;
            }

            // If too many vehicles are in the pool, don't spawn any more
            // vehicles until there's room.
            if (CPools::ms_pVehiclePool->GetNoOfFreeSpaces () < 5
                || carToSpawn == -1)
                return;

            CVehicle *vehicle
                = GameUtil::CreateVehicle (carToSpawn, spawnPosition,
                                           RandomHelper::Random (0.0f, 360.0f),
                                           false);

            if (vehicle)
            {
                vehicle->m_vecMoveSpeed.z -= 5.0f;
                vehicle->m_fHealth = 249.0f;

                vehicleList[vehicle] = 0;
            }
        }
    }

    wait = Random (500, 3000);
}
