#include <util/EffectBase.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class SwapVehiclesOnImpactEffect : public EffectBase
{
    static inline ThiscallEvent<
        AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL,
                    0x54C435, H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL,
                    0x54D3FE, H_CALL, 0x54D4D2, H_CALL>,
        PRIORITY_AFTER,
        ArgPick<ArgTypes<CPhysical *, CPhysical *, int, float *, int>, 0, 1, 2,
                3, 4>,
        void (CPhysical *, CPhysical *, int, float *, int)>
        applyCollisionEvent;

    static inline bool collisionHappened = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        collisionHappened = false;

        applyCollisionEvent += ApplyCollision;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        applyCollisionEvent -= ApplyCollision;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (collisionHappened)
        {
            inst->Disable ();
        }
    }

    static void
    ApplyCollision (CPhysical *thisEntity, CPhysical *otherEntity, int a3,
                    float *a4, int a5)
    {
        if (thisEntity->m_nType != eEntityType::ENTITY_TYPE_VEHICLE
            || otherEntity->m_nType != eEntityType::ENTITY_TYPE_VEHICLE)
        {
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (!player)
        {
            return;
        }

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (!playerVehicle)
        {
            return;
        }

        if (playerVehicle != thisEntity && playerVehicle != otherEntity)
        {
            return;
        }

        CVehicle *npcCar = playerVehicle == thisEntity
                               ? (CVehicle *) otherEntity
                               : (CVehicle *) thisEntity;

        CPed *npc = npcCar->m_pDriver;

        Command<
            eScriptCommands::COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
            player, playerVehicle);
        if (npc)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                npc, npcCar);
        }

        Command<eScriptCommands::COMMAND_WARP_CHAR_INTO_CAR> (player, npcCar);
        if (npc)
        {
            Command<eScriptCommands::COMMAND_WARP_CHAR_INTO_CAR> (
                npc, playerVehicle);

            Command<eScriptCommands::COMMAND_TASK_CAR_DRIVE_WANDER> (
                npc, playerVehicle, 20.0f,
                eCarDrivingStyle::DRIVINGSTYLE_PLOUGH_THROUGH);
        }

        Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

        collisionHappened = true;
    }
};

DEFINE_EFFECT (SwapVehiclesOnImpactEffect, "effect_swap_vehicles_on_impact", 0);