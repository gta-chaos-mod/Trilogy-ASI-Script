#include <util/Config.h>
#include <util/EffectBase.h>

using namespace plugin;

class YourCarFloatsAwayWhenHitEffect : public EffectBase
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

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            playerVehicle->m_nPhysicalFlags.bApplyGravity = true;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (collisionHappened)
        {
            applyCollisionEvent -= ApplyCollision;
            collisionHappened = false;

            if (!Config::GetOrDefault ("CrowdControl.Enabled", false))
            {
                inst->SetDuration (
                    std::min (inst->GetEffectRemaining (), 1000 * 30));
            }
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

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (!playerVehicle) return;

        if (playerVehicle == thisEntity || playerVehicle == otherEntity)
        {
            playerVehicle->m_nPhysicalFlags.bApplyGravity = false;
            collisionHappened                             = true;
        }
    }
};

DEFINE_EFFECT (YourCarFloatsAwayWhenHitEffect,
               "effect_your_car_floats_away_when_hit", 0);