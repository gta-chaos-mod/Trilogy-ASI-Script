#include <util/EffectBase.h>

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

        Events::processScriptsEvent += OnProcessScripts;

        injector::MakeCALL (0x61ECCD, Hooked_CWeapon_Fire);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::processScriptsEvent -= OnProcessScripts;

        injector::MakeCALL (0x61ECCD, 0x742300);
    }

    static void
    OnProcessScripts ()
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

    static char __fastcall Hooked_CWeapon_Fire (CWeapon *thisWeapon, void *edx,
                                                CPed *owner, CVector *vecOrigin,
                                                CVector *_vecEffectPosn,
                                                CEntity *targetEntity,
                                                CVector *vecTarget,
                                                CVector *arg_14)
    {
        if (owner == FindPlayerPed () && !FindPlayerVehicle (-1, false))
            recoilValue = 4.0f;

        return CallMethodAndReturn<char, 0x742300, CWeapon *> (
            thisWeapon, owner, vecOrigin, _vecEffectPosn, targetEntity,
            vecTarget, arg_14);
    }
};

DEFINE_EFFECT (WeaponRecoilEffect, "effect_weapon_recoil", 0);