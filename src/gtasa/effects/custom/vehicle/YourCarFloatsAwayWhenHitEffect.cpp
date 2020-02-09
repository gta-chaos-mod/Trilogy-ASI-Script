#include "YourCarFloatsAwayWhenHitEffect.h"

static ThiscallEvent<
    AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL, 0x54C435,
                H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL, 0x54D3FE, H_CALL,
                0x54D4D2, H_CALL>,
    PRIORITY_AFTER,
    ArgPick<ArgTypes<CVehicle *, CVehicle *, int, float *, int>, 0, 1, 2, 3, 4>,
    void (CVehicle *, CVehicle *, int, float *, int)>
    applyCollisionEvent;

bool YourCarFloatsAwayWhenHitEffect::collisionHappened = false;

YourCarFloatsAwayWhenHitEffect::YourCarFloatsAwayWhenHitEffect ()
    : EffectBase ("effect_your_car_floats_away_when_hit")
{
}

void
YourCarFloatsAwayWhenHitEffect::Enable ()
{
    EffectBase::Enable ();

    applyCollisionEvent += ApplyCollision;
}

void
YourCarFloatsAwayWhenHitEffect::Disable ()
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
YourCarFloatsAwayWhenHitEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (collisionHappened)
    {
        applyCollisionEvent -= ApplyCollision;
        collisionHappened = false;

        if (!Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            SetEffectRemaining (std::min (GetEffectRemaining (), 1000 * 30));
        }
    }
}

void
YourCarFloatsAwayWhenHitEffect::ApplyCollision (CVehicle *thisVehicle,
                                                CVehicle *a2, int a3, float *a4,
                                                int a5)
{
    CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
    if (!playerVehicle)
        return;

    if (playerVehicle == thisVehicle
            && a2->m_nType == eEntityType::ENTITY_TYPE_VEHICLE
        || playerVehicle == a2
               && thisVehicle->m_nType == eEntityType::ENTITY_TYPE_VEHICLE)
    {
        playerVehicle->m_nPhysicalFlags.bApplyGravity = false;

        collisionHappened = true;
    }
}
