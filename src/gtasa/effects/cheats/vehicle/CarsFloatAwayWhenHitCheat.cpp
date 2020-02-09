#include "CarsFloatAwayWhenHitCheat.h"

static ThiscallEvent<
    AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL, 0x54C435,
                H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL, 0x54D3FE, H_CALL,
                0x54D4D2, H_CALL>,
    PRIORITY_AFTER,
    ArgPick<ArgTypes<CVehicle *, CVehicle *, int, float *, int>, 0, 1, 2, 3, 4>,
    void (CVehicle *, CVehicle *, int, float *, int)>
    applyCollisionEvent;

CarsFloatAwayWhenHitCheat::CarsFloatAwayWhenHitCheat ()
    : EffectBase ("cheat_cars_float_away_when_hit")
{
}

void
CarsFloatAwayWhenHitCheat::Enable ()
{
    EffectBase::Enable ();

    applyCollisionEvent += ApplyCollision;
}

void
CarsFloatAwayWhenHitCheat::Disable ()
{
    applyCollisionEvent -= ApplyCollision;

    CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
    if (playerVehicle)
    {
        playerVehicle->m_nPhysicalFlags.bApplyGravity = true;
    }

    EffectBase::Disable ();
}

void
CarsFloatAwayWhenHitCheat::ApplyCollision (CVehicle *thisVehicle, CVehicle *a2,
                                           int a3, float *a4, int a5)
{
    CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
    if (!playerVehicle)
        return;

    if (playerVehicle == thisVehicle)
    {
        a2->m_nPhysicalFlags.bApplyGravity = false;
    }
    if (playerVehicle == a2)
    {
        thisVehicle->m_nPhysicalFlags.bApplyGravity = false;
    }
}
