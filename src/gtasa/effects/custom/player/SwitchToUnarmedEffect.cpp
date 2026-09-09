#include "util/EffectBase.h"
#include "util/GameUtil.h"

class SwitchToUnarmedEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !CanActivate ()) return;

        player->SetCurrentWeapon (WEAPONTYPE_UNARMED);
        inst->Disable ();
    }
};

DEFINE_EFFECT (SwitchToUnarmedEffect, "effect_switch_to_unarmed", 0);
