#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/MathHelper.h"

class StruckByTruckEffect : public EffectBase
{
    int wait = 700;

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

        wait = 700;

        inst->SetTimerVisible (false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 25.0f, 0.0f));

        // Linerunner
        CAutomobile *vehicle = (CAutomobile *) GameUtil::CreateVehicle (
            403, position, player->m_fCurrentRotation - M_PI, true);

        vehicle->PlaceOnRoadProperly ();

        CMatrix *matrix   = vehicle->GetMatrix ();
        float    velocity = 1.0f;

        vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
        vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
        vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;

        inst->Disable ();
    }
};

DEFINE_EFFECT (StruckByTruckEffect, "effect_struck_by_truck", 0);
