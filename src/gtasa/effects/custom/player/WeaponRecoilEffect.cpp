#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

#include <CMenuSystem.h>
#include <CTaskSimpleGangDriveBy.h>

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
                          0x61ECCD, 0x686787);

        HOOK_METHOD_ARGS (inst, Hooked_CTaskSimpleGangDriveBy_FireGun,
                          char (CTaskSimpleGangDriveBy *, CPed * ped), 0x51A3FD,
                          0x62D60D);
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        if (recoilValue <= 0.0f) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (pad) pad->NewMouseControllerState.y += recoilValue;

        recoilValue
            = std::max (0.0f, recoilValue
                                  - (float) GenericUtil::CalculateTick (0.5f));
    }

    static char
    Hooked_CWeapon_Fire (auto &&cb, CWeapon *thisWeapon, CPed *owner,
                         CVector *vecOrigin, CVector *_vecEffectPosn,
                         CEntity *targetEntity, CVector *vecTarget,
                         CVector *arg_14)
    {
        if (!owner->IsPlayer ()) return cb ();

        if (FindPlayerVehicle (-1, false)) return cb ();

        recoilValue = 16.0f;

        if (thisWeapon->m_eWeaponType == WEAPONTYPE_SNIPERRIFLE)
            recoilValue *= 4.0f;

        return cb ();
    }

    static char
    Hooked_CTaskSimpleGangDriveBy_FireGun (auto                  &&cb,
                                           CTaskSimpleGangDriveBy *thisTask,
                                           CPed                   *owner)
    {
        if (owner == FindPlayerPed ())
        {
            recoilValue = 16.0f;
        }

        return cb ();
    }
};

DEFINE_EFFECT (WeaponRecoilEffect, "effect_weapon_recoil", 0);