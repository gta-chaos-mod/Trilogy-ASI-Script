#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include "cHandlingDataMgr.h"

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
        return FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            position  = vehicle->GetPosition ();
            moveSpeed = vehicle->m_vecMoveSpeed;
            turnSpeed = vehicle->m_vecTurnSpeed;
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (vehicle)
        {
            vehicle->m_vecMoveSpeed = moveSpeed;
            vehicle->m_vecTurnSpeed = turnSpeed;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (vehicle)
        {
            vehicle->SetPosn (position);
            vehicle->m_vecMoveSpeed = {0, 0, 0};
            vehicle->m_vecTurnSpeed = {0, 0, 0};
        }
    }
};

DEFINE_EFFECT (FreezeVehicleEffect, "effect_freeze_vehicle", 0);