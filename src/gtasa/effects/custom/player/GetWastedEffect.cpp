#include <util/EffectBase.h>

#include "CCutsceneMgr.h"

class GetWastedEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && player->CanSetPedState ())
        {
            player->SetPedState (ePedState::PEDSTATE_DEAD);

            CCutsceneMgr::SkipCutscene ();

            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (GetWastedEffect, "effect_get_wasted", GROUP_HEALTH);