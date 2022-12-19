#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveShotgunEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_SHOTGSPA, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_SPAS12, 50, 1);

        CStreaming::SetModelIsDeletable (MODEL_SHOTGSPA);
    }
};

DEFINE_EFFECT (GiveShotgunEffect, "effect_give_shotgun", GROUP_WEAPONS);