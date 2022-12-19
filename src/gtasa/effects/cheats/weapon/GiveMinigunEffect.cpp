#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveMinigunEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_MINIGUN, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_MINIGUN, 100, 1);

        CStreaming::SetModelIsDeletable (MODEL_MINIGUN);
    }
};

DEFINE_EFFECT (GiveMinigunEffect, "effect_give_minigun", GROUP_WEAPONS);