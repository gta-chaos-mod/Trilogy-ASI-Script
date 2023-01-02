#include "util/EffectBase.h"
#include "util/GameUtil.h"

class GetBustedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !GameUtil::IsPlayerSafe ())
        {
            inst->ResetTimer ();
            return;
        }

        player->SetPedState (PEDSTATE_ARRESTED);

        inst->Disable ();
    }
};

DEFINE_EFFECT (GetBustedEffect, "effect_get_busted", GROUP_HEALTH);