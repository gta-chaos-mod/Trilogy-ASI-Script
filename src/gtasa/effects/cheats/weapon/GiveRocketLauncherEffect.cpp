#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveRocketLauncherEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_HEATSEEK, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_RLAUNCHER_HS, 10, 1);

        CStreaming::SetModelIsDeletable (MODEL_HEATSEEK);
    }
};

DEFINE_EFFECT (GiveRocketLauncherEffect, "effect_give_rocket_launcher",
               GROUP_WEAPONS);