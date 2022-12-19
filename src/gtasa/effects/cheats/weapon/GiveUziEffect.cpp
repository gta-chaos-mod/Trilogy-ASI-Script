#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveUziEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_MICRO_UZI, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_MICRO_UZI, 100, 1);

        CStreaming::SetModelIsDeletable (MODEL_MICRO_UZI);
    }
};

DEFINE_EFFECT (GiveUziEffect, "effect_give_uzi", GROUP_WEAPONS);