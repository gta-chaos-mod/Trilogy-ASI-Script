#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/GenericUtil.h>
#include <util/MathHelper.h>

class CarmageddonEffect : public EffectBase
{
    int                       wait        = 0;
    std::map<CVehicle *, int> vehicleList = {};
    std::vector<int>          possibleVehicles
        = {400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412,
           413, 414, 415, 416, 418, 419, 420, 421, 422, 423, 424, 426, 427,
           428, 429, 431, 433, 434, 436, 437, 438, 439, 440, 442, 443, 444,
           445, 448, 451, 455, 456, 457, 458, 459, 461, 462, 463, 466, 467,
           468, 470, 471, 474, 475, 477, 478, 479, 480, 482, 483, 485, 489,
           490, 491, 492, 494, 495, 496, 498, 499, 500, 502, 503, 504, 505,
           506, 507, 508, 516, 517, 518, 521, 522, 523, 525, 526, 527, 528,
           529, 530, 531, 533, 534, 535, 536, 538, 540, 541, 542, 543, 545,
           546, 547, 549, 550, 551, 552, 554, 555, 558, 559, 560, 561, 562,
           565, 566, 567, 568, 571, 572, 574, 575, 576, 579, 580, 581, 582,
           583, 585, 586, 587, 588, 589, 596, 597, 598, 599, 600, 602, 603};

public:
    void
    OnTick (EffectInstance *inst) override
    {
        int step = (int) GenericUtil::CalculateTick ();

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
            // Spawn a vehicle at a specified distance and a random angle from
            // the player
            float   spawnDistance = GetSpawnDistance ();
            CVector spawnPosition = player->TransformFromObjectSpace (
                CVector (0.0f, spawnDistance, 50.0f));

            float thats_rad
                = MathHelper::ToRadians (inst->Random (0.0f, 360.0f));

            spawnPosition += CVector (30.0f * sin (thats_rad),
                                      30.0f * cos (thats_rad), 0.0f);

            for (int i = 0; i < inst->Random (1, 3); i++)
            {
                int carToSpawn = possibleVehicles[inst->Random (
                    0, (int) possibleVehicles.size () - 1)];

                // If too many vehicles are loaded, choose an already loaded
                // vehicle. Game limit is 22.
                int loadedVehicles
                    = CStreaming::ms_vehiclesLoaded.CountMembers ();
                if (loadedVehicles > 20)
                    carToSpawn = CStreaming::ms_vehiclesLoaded.GetMember (
                        inst->Random (0, loadedVehicles - 1));

                // Non valid vehicle
                if (std::find (possibleVehicles.begin (),
                               possibleVehicles.end (), carToSpawn)
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
                                               inst->Random (0.0f, 360.0f),
                                               false);

                if (vehicle)
                {
                    vehicle->m_vecMoveSpeed.z -= 5.0f;
                    vehicle->m_fHealth = 249.0f;

                    vehicleList[vehicle] = 0;
                }
            }
        }

        wait = inst->Random (500, 3000);
    }

    void
    RemoveExplodedVehicles (int step)
    {
        const int DESPAWN_TIME = 5000;

        for (auto it = vehicleList.begin (); it != vehicleList.end (); ++it)
        {
            CVehicle *vehicle = it->first;
            int      &time    = it->second;

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
    GetSpawnDistance ()
    {
        float spawnDistance = 0.0f;

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
            spawnDistance
                += playerVehicle->m_vecMoveSpeed.Magnitude2D () * 4.2f;

        return spawnDistance;
    }
};

DEFINE_EFFECT (CarmageddonEffect, "effect_carmageddon", 0);