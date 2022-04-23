#include "util/EffectBase.h"
#include "util/GameUtil.h"

class SwitchToUnarmedEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && CanActivate ())
        {
            player->SetCurrentWeapon (eWeaponType::WEAPON_UNARMED);
            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (SwitchToUnarmedEffect, "effect_switch_to_unarmed", 0);
