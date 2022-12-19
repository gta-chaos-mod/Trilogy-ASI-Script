#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveGrenadesEffect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_GRENADE, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_GRENADE, 10, 1);

        CStreaming::SetModelIsDeletable (MODEL_GRENADE);
    }
};

DEFINE_EFFECT (GiveGrenadesEffect, "effect_give_grenades", GROUP_WEAPONS);