#include "util/EffectBase.h"
#include "util/GameUtil.h"

class GetWastedEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !GameUtil::IsPlayerSafe ())
        {
            inst->ResetTimer ();
            return;
        }

        player->SetPedState (PEDSTATE_DEAD);

        inst->Disable ();
    }
};

DEFINE_EFFECT (GetWastedEffect, "effect_get_wasted", GROUP_HEALTH);