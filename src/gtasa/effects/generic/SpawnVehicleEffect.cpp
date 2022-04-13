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
                        false);
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

                    auto moveSpeed = vehicle->m_vecMoveSpeed;
                    auto turnSpeed = vehicle->m_vecTurnSpeed;
                    auto matrix    = vehicle->GetMatrix ();
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

                    memset ((void *) vehicle, 0, sizeof (CHeli));
                    switch (reinterpret_cast<CVehicleModelInfo *> (
                                CModelInfo::ms_modelInfoPtrs[vehicleID])
                                ->m_nVehicleType)
                    {
                    case VEHICLE_MTRUCK:
                        plugin::CallMethod<0x6C8D60> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_QUAD:
                        plugin::CallMethod<0x6CE370> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_HELI:
                        plugin::CallMethod<0x6C4190> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_PLANE:
                        plugin::CallMethod<0x6C8E20> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_BIKE:
                        plugin::CallMethod<0x6BF430> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_BMX:
                        plugin::CallMethod<0x6BF820> (vehicle, vehicleID, 1);
                        reinterpret_cast<CBmx *> (vehicle)->m_nDamageFlags
                            |= 0x10;
                        break;
                    case VEHICLE_TRAILER:
                        plugin::CallMethod<0x6D03A0> (vehicle, vehicleID, 1);
                        break;
                    case VEHICLE_BOAT:
                    case VEHICLE_TRAIN: // Thank you Rockstar, very cool
                        plugin::CallMethod<0x6F2940> (vehicle, vehicleID, 1);
                        break;
                    default:
                        plugin::CallMethod<0x6B0A90> (vehicle, vehicleID, 1, 1);
                        break;
                    }

                    vehicle->m_matrix       = matrix;
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
