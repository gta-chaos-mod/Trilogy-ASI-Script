#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class FreezeVehicleEffect : public EffectBase
{
    CVehicle *vehicle;
    CVector   position;
    CVector   moveSpeed;
    CVector   turnSpeed;

public:
    bool
    CanActivate () override
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return false;

        if (Command<eScriptCommands::COMMAND_IS_RECORDING_GOING_ON_FOR_CAR> (
                vehicle))
            return false;

        return true;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle)
        {
            inst->Disable ();
            return;
        }

        position  = vehicle->GetPosition ();
        moveSpeed = vehicle->m_vecMoveSpeed;
        turnSpeed = vehicle->m_vecTurnSpeed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (!vehicle) return;

        vehicle->m_nPhysicalFlags.bDisableMoveForce = false;

        vehicle->m_vecMoveSpeed = moveSpeed;
        vehicle->m_vecTurnSpeed = turnSpeed;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!vehicle) return;

        vehicle->m_nPhysicalFlags.bDisableMoveForce = true;

        vehicle->SetPosn (position);
        vehicle->m_vecMoveSpeed = {0, 0, 0};
        vehicle->m_vecTurnSpeed = {0, 0, 0};
    }
};

DEFINE_EFFECT (FreezeVehicleEffect, "effect_freeze_vehicle", 0);