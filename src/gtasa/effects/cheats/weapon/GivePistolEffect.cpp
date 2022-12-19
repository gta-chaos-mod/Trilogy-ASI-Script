#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GivePistolEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_SILENCED, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_PISTOL_SILENCED, 50, 1);

        CStreaming::SetModelIsDeletable (MODEL_SILENCED);
    }
};

DEFINE_EFFECT (GivePistolEffect, "effect_give_pistol", GROUP_WEAPONS);