#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CCheat.h>

class NoShootingAllowedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_Fire,
                          char (CWeapon *, CPed *, CVector *, CVector *,
                                CEntity *, CVector *, CVector *),
                          0x61ECCD);

        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_FireFromCar,
                          char (CWeapon *, CVehicle *, char, char), 0x742280);
    }

    static char
    Hooked_CWeapon_Fire (auto &&cb, CWeapon *thisWeapon, CPed *owner,
                         CVector *vecOrigin, CVector *_vecEffectPosn,
                         CEntity *targetEntity, CVector *vecTarget,
                         CVector *arg_14)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (owner == player) CCheat::SuicideCheat ();

        return cb ();
    }

    static char
    Hooked_CWeapon_FireFromCar (auto &&cb, CWeapon *thisWeapon,
                                CVehicle *vehicle, char leftSide,
                                char rightSide)
    {
        // TODO: Fix this for Just Business
        // Player is passenger so we have to hook a different method
        CPlayerPed *player = FindPlayerPed ();
        if (player && vehicle == FindPlayerVehicle (-1, false))
        {
            CCheat::SuicideCheat ();
        }

        return cb ();
    }
};

DEFINE_EFFECT (NoShootingAllowedEffect, "effect_no_shooting_allowed",
               GROUP_HEALTH);