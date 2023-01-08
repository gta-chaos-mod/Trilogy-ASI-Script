#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class WeaponSet4Effect : public OneTimeEffect
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

        player->GiveWeapon (WEAPON_MINIGUN, 500, 1);

        CStreaming::SetModelIsDeletable (MODEL_MINIGUN);
    }
};

DEFINE_EFFECT (WeaponSet4Effect, "effect_weapon_set_4", GROUP_WEAPONS);