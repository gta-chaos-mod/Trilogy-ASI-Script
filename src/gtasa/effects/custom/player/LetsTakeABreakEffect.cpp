#include <util/EffectBase.h>

class LetsTakeABreakEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && player->GetPadFromPlayer ())
        {
            player->GetPadFromPlayer ()->DisablePlayerControls = false;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && player->GetPadFromPlayer ())
        {
            player->GetPadFromPlayer ()->DisablePlayerControls = true;
        }
    }
};

DEFINE_EFFECT (LetsTakeABreakEffect, "effect_lets_take_a_break",
               GROUP_CONTROLS);