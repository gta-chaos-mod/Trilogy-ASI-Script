#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CTaskSimpleGangDriveBy.h>
#include <CTheScripts.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

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

        HOOK_METHOD_ARGS (inst, Hooked_CTaskSimpleGangDriveBy_FireGun,
                          char (CTaskSimpleGangDriveBy *, CPed * ped), 0x51A3FD,
                          0x62D60D);

        HOOK_METHOD_ARGS (inst, Hooked_CVehicle_FirePlaneGuns,
                          void (CVehicle *), 0x6E3A17);

        HOOK_METHOD_ARGS (inst,
                          Hooked_CVehicle_PossiblyDropFreeFallBombForPlayer,
                          char (CVehicle *, int, bool), 0x6E3A27);

        HOOK_METHOD_ARGS (inst, Hooked_CVehicle_FireHeatSeakingMissile,
                          char (CVehicle *, CEntity *, bool), 0x6E3A72);

        HOOK_METHOD_ARGS (inst, Hooked_CVehicle_FireUnguidedMissile,
                          char (CVehicle *, int, bool), 0x6E3A82);
    }

    static char
    Hooked_CWeapon_Fire (auto &&cb, CWeapon *thisWeapon, CPed *owner,
                         CVector *vecOrigin, CVector *_vecEffectPosn,
                         CEntity *targetEntity, CVector *vecTarget,
                         CVector *arg_14)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (owner == player)
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (owner, 0);

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
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (player, 0);
        }

        return cb ();
    }

    static char
    Hooked_CTaskSimpleGangDriveBy_FireGun (auto                  &&cb,
                                           CTaskSimpleGangDriveBy *thisTask,
                                           CPed                   *owner)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (owner == player)
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (owner, 0);

        return cb ();
    }

    static void
    Hooked_CVehicle_FirePlaneGuns (auto &&cb, CVehicle *vehicle)
    {
        CPed *driver = vehicle->m_pDriver;

        if (driver && driver->IsPlayer ())
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (driver, 0);

        cb ();
    }

    static char
    Hooked_CVehicle_PossiblyDropFreeFallBombForPlayer (auto    &&cb,
                                                       CVehicle *vehicle,
                                                       int       positionType,
                                                       bool      checkTime)
    {
        CPed *driver = vehicle->m_pDriver;

        if (driver && driver->IsPlayer ())
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (driver, 0);

        return cb ();
    }

    static char
    Hooked_CVehicle_FireHeatSeakingMissile (auto &&cb, CVehicle *vehicle,
                                            CEntity *targetEntity,
                                            bool     checkTime)
    {
        CPed *driver = vehicle->m_pDriver;

        if (driver && driver->IsPlayer ())
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (driver, 0);

        return cb ();
    }

    static char
    Hooked_CVehicle_FireUnguidedMissile (auto &&cb, CVehicle *vehicle,
                                         int positionType, bool checkTime)
    {
        CPed *driver = vehicle->m_pDriver;

        if (driver && driver->IsPlayer ())
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (driver, 0);

        return cb ();
    }
};

DEFINE_EFFECT (NoShootingAllowedEffect, "effect_no_shooting_allowed",
               GROUP_HEALTH);