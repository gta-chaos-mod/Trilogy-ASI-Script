#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveSniperEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_SNIPER, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_SNIPERRIFLE, 20, 1);

        CStreaming::SetModelIsDeletable (MODEL_SNIPER);
    }
};

DEFINE_EFFECT (GiveSniperEffect, "effect_give_sniper", GROUP_WEAPONS);