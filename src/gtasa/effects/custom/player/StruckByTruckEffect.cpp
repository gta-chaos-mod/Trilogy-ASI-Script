#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/MathHelper.h"

class StruckByTruckEffect : public EffectBase
{
    CAutomobile *linerunner = nullptr;
    int          wait       = 700;

public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();

        return player && !player->m_nAreaCode && GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();

        linerunner = nullptr;
        wait       = 700;

        inst->SetTimerVisible (false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        SpawnOrUpdateTruck ();

        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        linerunner->PlaceOnRoadProperly ();

        CMatrix *matrix   = linerunner->GetMatrix ();
        float    velocity = 1.0f;

        linerunner->m_vecMoveSpeed.x = velocity * matrix->up.x;
        linerunner->m_vecMoveSpeed.y = velocity * matrix->up.y;
        linerunner->m_vecMoveSpeed.z = velocity * matrix->up.z;

        inst->Disable ();
    }

    void
    SpawnOrUpdateTruck ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 25.0f, 0.0f));

        float playerFacing = player->m_fCurrentRotation - M_PI;

        if (linerunner)
        {
            linerunner->SetPosn (position);
            linerunner->SetOrientation (0.0f, 0.0f, playerFacing);
            return;
        }

        // Linerunner
        linerunner
            = (CAutomobile *) GameUtil::CreateVehicle (403, position,
                                                       playerFacing, true);

        linerunner->PlaceOnRoadProperly ();
    }
};

DEFINE_EFFECT (StruckByTruckEffect, "effect_struck_by_truck", 0);
