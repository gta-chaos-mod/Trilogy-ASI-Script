#include "effects/OneTimeEffect.h"

#include <util/EffectInstance.h>
#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnVehicleEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *instance)
    {
        SpawnForPlayer (instance->GetCustomData ().value ("vehicleID", 400),
                        true);
    }

    void
    SpawnForPlayer (int vehicleID, bool setPlayerAsDriver)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && !player->m_nAreaCode)
        {
            if (setPlayerAsDriver)
            {
                // TODO: Fix this somehow
                std::vector<CPed *> passengers = {};

                CVehicle *vehicle = FindPlayerVehicle (-1, false);
                if (vehicle)
                {
                    CStreaming::RequestModel (vehicleID, 1);
                    CStreaming::LoadAllRequestedModels (0);

                    auto     oldPosition = vehicle->GetPosition ();
                    auto     moveSpeed   = vehicle->m_vecMoveSpeed;
                    auto     turnSpeed   = vehicle->m_vecTurnSpeed;
                    RwMatrix oldMatrix;
                    vehicle->GetMatrix ()->CopyToRwMatrix (&oldMatrix);
                    auto createdBy = vehicle->m_nCreatedBy;

                    Command<
                        eScriptCommands::
                            COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                        FindPlayerPed (), vehicle);

                    for (CPed *ped : vehicle->m_apPassengers)
                    {
                        if (ped)
                        {
                            passengers.push_back (ped);
                            Command<
                                eScriptCommands::
                                    COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                                ped, vehicle);
                        }
                    }

                    CVehicle *temporaryVehicle
                        = GameUtil::CreateVehicle (vehicleID, oldPosition, 0.0f,
                                                   false);

                    int oldRef = CPools::ms_pVehiclePool->GetRef (vehicle);
                    int newRef
                        = CPools::ms_pVehiclePool->GetRef (temporaryVehicle);

                    // Allocate space
                    CHeli *heli = (CHeli *) malloc (sizeof (CHeli));
                    // Move the current vehicle into empty space
                    memcpy (heli, vehicle, sizeof (CHeli));
                    // Move the new vehicle into the current vehicle memory
                    memcpy (vehicle, temporaryVehicle, sizeof (CHeli));
                    // Move the current vehicle from the empty space to the new
                    // vehicle memory
                    memcpy (temporaryVehicle, heli, sizeof (CHeli));
                    // Free space
                    free (heli);

                    // TODO: Game crashes when we try to delete the vehicle.
                    // Some refs not updated properly?
                    // This opcode is at 0x467B1E

                    // std::swap (CPools::ms_pVehiclePool[oldRef],
                    //            CPools::ms_pVehiclePool[newRef]);
                    // std::swap (CPools::ms_pVehiclePool->m_byteMap[oldIndex],
                    //            CPools::ms_pVehiclePool->m_byteMap[newIndex]);

                    // std::swap (temporaryVehicle, vehicle);
                    // CWorld::Remove (temporaryVehicle);
                    // Command<eScriptCommands::COMMAND_DELETE_CAR> (
                    //     temporaryVehicle);

                    CallMethod<0x59AD20, CMatrix *, RwMatrix *> (
                        vehicle->GetMatrix (), &oldMatrix);
                    vehicle->m_vecMoveSpeed = moveSpeed;
                    vehicle->m_vecTurnSpeed = turnSpeed;
                    vehicle->m_nCreatedBy   = createdBy;

                    Command<eScriptCommands::COMMAND_WARP_CHAR_INTO_CAR> (
                        player, vehicle);
                    if (passengers.size () > 0)
                    {
                        for (unsigned int i = 0; i < vehicle->m_nMaxPassengers
                                                 && i < passengers.size ();
                             i++)
                        {
                            Command<
                                eScriptCommands::
                                    COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER> (
                                passengers[i], vehicle, i);
                        }
                    }
                }

                /*CVehicle* vehicle = GameUtil::CreateVehicle(this->vehicleID,
                position, player->m_fCurrentRotation, true); if
                (playerWasInVehicle) { vehicle->m_vecMoveSpeed = moveSpeed;
                vehicle->m_vecTurnSpeed = turnSpeed; vehicle->SetMatrix(matrix);
                vehicle->m_nCreatedBy = createdBy; vehicle->m_pDriver =
                playerVehicle->m_pDriver;
                }*/

                Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
            }
            else
            {
                CVector position = player->TransformFromObjectSpace (
                    CVector (0.0f, 5.0f, 0.0f));
                CVehicle *vehicle
                    = GameUtil::CreateVehicle (vehicleID, position,
                                               player->m_fCurrentRotation
                                                   + 1.5707964f,
                                               false);
            }
        }
    }
};

DEFINE_EFFECT (SpawnVehicleEffect, "effect_spawn_vehicle", 0);
