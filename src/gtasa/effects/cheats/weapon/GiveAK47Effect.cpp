#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class GiveAK47Effect : public OneTimeEffect
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

        CStreaming::RequestModel (MODEL_AK47, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_AK47, 50, 1);

        CStreaming::SetModelIsDeletable (MODEL_AK47);
    }
};

DEFINE_EFFECT (GiveAK47Effect, "effect_give_ak47", GROUP_WEAPONS);