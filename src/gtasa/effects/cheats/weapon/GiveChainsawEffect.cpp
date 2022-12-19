#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveChainsawEffect : public OneTimeEffect
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
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CStreaming::RequestModel (MODEL_CHNSAW, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_CHAINSAW, 1, 1);

        CStreaming::SetModelIsDeletable (MODEL_CHNSAW);
    }
};

DEFINE_EFFECT (GiveChainsawEffect, "effect_give_chainsaw", GROUP_WEAPONS);