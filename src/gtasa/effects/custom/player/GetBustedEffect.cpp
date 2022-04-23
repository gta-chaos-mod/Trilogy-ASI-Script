#include <util/EffectBase.h>

#include <CCutsceneMgr.h>

class GetBustedEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && player->CanSetPedState ())
        {
            player->SetPedState (ePedState::PEDSTATE_ARRESTED);

            CCutsceneMgr::SkipCutscene ();

            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (GetBustedEffect, "effect_get_busted", GROUP_HEALTH);