#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

// TODO: Add support for snipers
class WeaponRecoilEffect : public EffectBase
{
    static inline float recoilValue = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        recoilValue = 0.0f;

        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_Fire,
                          char (CWeapon *, CPed *, CVector *, CVector *,
                                CEntity *, CVector *, CVector *),
                          0x61ECCD);
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (recoilValue > 0.0f)
        {
            CPlayerPed *player = FindPlayerPed ();
            if (player)
            {
                CPad *pad = player->GetPadFromPlayer ();
                if (pad) pad->NewMouseControllerState.Y += recoilValue;
            }

            recoilValue -= 1.0f;
        }
    }

    static char __fastcall Hooked_CWeapon_Fire (auto &&cb, CWeapon *thisWeapon,
                                                CPed *owner, CVector *vecOrigin,
                                                CVector *_vecEffectPosn,
                                                CEntity *targetEntity,
                                                CVector *vecTarget,
                                                CVector *arg_14)
    {
        if (owner == FindPlayerPed () && !FindPlayerVehicle (-1, false))
            recoilValue = 4.0f;

        return cb ();
    }
};

DEFINE_EFFECT (WeaponRecoilEffect, "effect_weapon_recoil", 0);