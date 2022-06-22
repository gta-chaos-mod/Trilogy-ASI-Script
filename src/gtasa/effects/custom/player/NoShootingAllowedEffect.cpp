#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CCheat.h>
#include <CTaskSimpleGangDriveBy.h>

class NoShootingAllowedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_Fire,
                          char (CWeapon *, CPed *, CVector *, CVector *,
                                CEntity *, CVector *, CVector *),
                          0x61ECCD, 0x686787);

        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_FireFromCar,
                          char (CWeapon *, CVehicle *, char, char), 0x742280);

        // TODO: Doesn't work for Just Business
        HOOK_METHOD_ARGS (inst, Hooked_CTaskSimpleGangDriveBy_FireGun,
                          char (CTaskSimpleGangDriveBy *, CPed * ped), 0x51A3FD,
                          0x62D60D);
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
        CPlayerPed *player = FindPlayerPed ();
        if (player && vehicle == FindPlayerVehicle (-1, false))
        {
            CCheat::SuicideCheat ();
        }

        return cb ();
    }

    static char
    Hooked_CTaskSimpleGangDriveBy_FireGun (auto                  &&cb,
                                           CTaskSimpleGangDriveBy *thisTask,
                                           CPed                   *owner)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (owner == player) CCheat::SuicideCheat ();

        return cb ();
    }
};

DEFINE_EFFECT (NoShootingAllowedEffect, "effect_no_shooting_allowed",
               GROUP_HEALTH);