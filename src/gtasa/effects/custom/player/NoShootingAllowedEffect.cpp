#include "util/EffectBase.h"

#include <CCheat.h>

using namespace plugin;

// TODO: Add support for snipers
class NoShootingAllowedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x61ECCD, Hooked_CWeapon_Fire);
        injector::MakeCALL (0x742280, Hooked_CWeapon_FireFromCar);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::MakeCALL (0x61ECCD, 0x742300);
        injector::MakeCALL (0x742280, 0x73FA20);
    }

    static char __fastcall Hooked_CWeapon_Fire (CWeapon *thisWeapon, void *edx,
                                                CPed *owner, CVector *vecOrigin,
                                                CVector *_vecEffectPosn,
                                                CEntity *targetEntity,
                                                CVector *vecTarget,
                                                CVector *arg_14)
    {
        if (owner == FindPlayerPed ()) CCheat::SuicideCheat ();

        return CallMethodAndReturn<char, 0x742300, CWeapon *> (
            thisWeapon, owner, vecOrigin, _vecEffectPosn, targetEntity,
            vecTarget, arg_14);
    }

    static char __fastcall Hooked_CWeapon_FireFromCar (CWeapon  *thisWeapon,
                                                       void     *edx,
                                                       CVehicle *vehicle,
                                                       char      leftSide,
                                                       char      rightSide)
    {
        if (vehicle == FindPlayerVehicle(-1, false)) CCheat::SuicideCheat ();

        return CallMethodAndReturn<char, 0x73FA20, CWeapon *> (thisWeapon,
                                                               vehicle,
                                                               leftSide,
                                                               rightSide);
    }
};

DEFINE_EFFECT (NoShootingAllowedEffect, "effect_no_shooting_allowed",
               GROUP_HEALTH);