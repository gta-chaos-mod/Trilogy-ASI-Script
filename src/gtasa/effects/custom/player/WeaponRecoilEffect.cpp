#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

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

            recoilValue -= GenericUtil::CalculateTick (0.5f);
        }
    }

    static char
    Hooked_CWeapon_Fire (auto &&cb, CWeapon *thisWeapon, CPed *owner,
                         CVector *vecOrigin, CVector *_vecEffectPosn,
                         CEntity *targetEntity, CVector *vecTarget,
                         CVector *arg_14)
    {
        if (owner == FindPlayerPed () && !FindPlayerVehicle (-1, false))
        {
            recoilValue = 16.0f;

            if (thisWeapon->m_nType == WEAPON_SNIPERRIFLE)
            {
                recoilValue *= 4.0f;
            }
        }

        return cb ();
    }
};

DEFINE_EFFECT (WeaponRecoilEffect, "effect_weapon_recoil", 0);