#include "util/EffectBase.h"
#include "util/EffectInstance.h"
#include "util/GameUtil.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnVehicleEffect : public EffectBase
{
    bool                warpIntoCar = false;
    CVehicle           *oldVehicle  = nullptr;
    CVehicle           *newVehicle  = nullptr;
    std::vector<CPed *> passengers  = {};

public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();

        return player && !player->m_nAreaCode;
    }

    void
    OnStart (EffectInstance *instance)
    {
        instance->SetIsOneTimeEffect ();

        oldVehicle = nullptr;
        newVehicle = nullptr;
        passengers.clear ();
    }

    void
    OnTick (EffectInstance *inst)
    {
        if (!CanActivate ()) return;

        if (!newVehicle)
        {
            SpawnForPlayer (inst->GetCustomData ().value ("vehicleID", 400));

            return;
        }

        if (newVehicle && warpIntoCar)
        {
            Command<eScriptCommands::COMMAND_WARP_CHAR_INTO_CAR> (
                FindPlayerPed (), newVehicle);
            if (passengers.size () > 0)
            {
                for (unsigned int i = 0;
                     i < newVehicle->m_nMaxPassengers && i < passengers.size ();
                     i++)
                {
                    Command<eScriptCommands::
                                COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER> (
                        passengers[i], newVehicle, i);
                }
            }
        }

        if (oldVehicle)
        {
            Command<eScriptCommands::COMMAND_DELETE_CAR> (oldVehicle);
        }

        inst->Disable ();
    }

    void
    SpawnForPlayer (int vehicleID, bool setPlayerAsDriver = false)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        warpIntoCar = setPlayerAsDriver;

        // Experimental code to swap vehicle pointers and their data.
        // Not fully functional, deleting the old car crashes the game because
        // the pool is borked. Also immediately loading a game afterwards
        // crashes, too
        if (setPlayerAsDriver)
        {
            oldVehicle = FindPlayerVehicle (-1, false);
            if (oldVehicle)
            {
                CStreaming::RequestModel (vehicleID, 1);
                CStreaming::LoadAllRequestedModels (false);
                CStreaming::SetModelIsDeletable (vehicleID);

                auto     oldPosition = oldVehicle->GetPosition ();
                auto     moveSpeed   = oldVehicle->m_vecMoveSpeed;
                auto     turnSpeed   = oldVehicle->m_vecTurnSpeed;
                RwMatrix oldMatrix;
                oldVehicle->GetMatrix ()->CopyToRwMatrix (&oldMatrix);
                auto createdBy = oldVehicle->m_nCreatedBy;

                Command<eScriptCommands::
                            COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                    FindPlayerPed (), oldVehicle);

                for (CPed *ped : oldVehicle->m_apPassengers)
                {
                    if (ped)
                    {
                        passengers.push_back (ped);
                        Command<
                            eScriptCommands::
                                COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                            ped, oldVehicle);
                    }
                }

                oldPosition.z += 3.0f;

                newVehicle = GameUtil::CreateVehicle (vehicleID, oldPosition,
                                                      0.0f, false);

                uint8_t veh1Bak[sizeof (CHeli)];
                uint8_t veh2Bak[sizeof (CHeli)];

                CReference *veh1Refs = oldVehicle->m_pReferences;
                CReference *veh2Refs = newVehicle->m_pReferences;

                memcpy (veh1Bak, oldVehicle, sizeof (CHeli));
                memcpy (veh2Bak, newVehicle, sizeof (CHeli));

                memcpy (newVehicle, veh1Bak, sizeof (CHeli));
                memcpy (oldVehicle, veh2Bak, sizeof (CHeli));

                // Audio
                CAEAudioEntity tempEntity;
                memcpy (&tempEntity, &oldVehicle->m_vehicleAudio,
                        sizeof (CAEAudioEntity));
                memcpy (&oldVehicle->m_vehicleAudio,
                        &newVehicle->m_vehicleAudio, sizeof (CAEAudioEntity));
                memcpy (&newVehicle->m_vehicleAudio, &tempEntity,
                        sizeof (CAEAudioEntity));

                auto ref1 = veh1Refs;
                while (ref1)
                {
                    newVehicle->RegisterReference (ref1->m_ppEntity);
                    oldVehicle->CleanUpOldReference (ref1->m_ppEntity);

                    ref1 = ref1->m_pNext;
                }

                auto ref2 = veh2Refs;
                while (ref2)
                {
                    oldVehicle->RegisterReference (ref2->m_ppEntity);
                    newVehicle->CleanUpOldReference (ref2->m_ppEntity);

                    ref2 = ref2->m_pNext;
                }

                CallMethod<0x59AD20, CMatrix *, RwMatrix *> (
                    newVehicle->GetMatrix (), &oldMatrix);
                newVehicle->m_vecMoveSpeed = moveSpeed;
                newVehicle->m_vecTurnSpeed = turnSpeed;
                newVehicle->m_nCreatedBy   = createdBy;
            }

            Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
        }
        else
        {
            CVector position
                = player->TransformFromObjectSpace (CVector (0.0f, 5.0f, 0.0f));
            newVehicle = GameUtil::CreateVehicle (vehicleID, position,
                                                  player->m_fCurrentRotation
                                                      + 1.5707964f,
                                                  true);

            newVehicle->m_nVehicleFlags.bHasBeenOwnedByPlayer = true;
        }
    }
};

DEFINE_EFFECT (SpawnVehicleEffect, "effect_spawn_vehicle", 0);
