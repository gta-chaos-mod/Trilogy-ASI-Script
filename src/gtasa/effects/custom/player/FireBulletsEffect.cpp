#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CFireManager.h>

class FireBulletsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_DoBulletImpact,
                          void (CWeapon *, CEntity *, CEntity *, CVector *,
                                CVector *, CColPoint *, int),
                          0x73CD92, 0x741199, 0x7411DF, 0x7412DF, 0x741E30);

        // Sniper Section //
        HOOK_ARGS (inst, Hooked_CWeapon_GenerateDamageEvent,
                   void (CPed *, CPed *, eWeaponType, int, int, char),
                   0x736306);

        HOOK_METHOD_ARGS (inst, Hooked_CVehicle_InflictDamage,
                          void (CVehicle *, CPed *, eWeaponType, float,
                                CVector),
                          0x73647F);

        HOOK_METHOD_ARGS (inst, Hooked_CObject_ObjectDamage,
                          void (CObject *, float, RwV3d *, RwV3d *, CEntity *,
                                eWeaponType),
                          0x736692, 0x7365E3);

        HOOK_STD_ARGS (inst, Hooked_Fx_c_AddBulletImpact,
                       void (RwV3d *, RwV3d *, int, signed int, float),
                       0x736545);
    }

    static void
    StartFireAt (CEntity *owner, CEntity *victim)
    {
        gFireManager.StartFire (victim, owner, 1.0f, 0, 2000, 0);
    }

    static void
    StartFireAt (CEntity *owner, CVector point)
    {
        gFireManager.StartFire (point, 1.0f, 0, owner, 2000, 0, 1);
    }

    static void
    Hooked_CWeapon_DoBulletImpact (auto &&cb, CWeapon *weapon, CEntity *owner,
                                   CEntity *victim, CVector *startPoint,
                                   CVector *endPoint, CColPoint *colPoint,
                                   int a7)
    {
        if (owner == FindPlayerPed ())
        {
            CVector point = colPoint->m_vecPoint;

            bool validVictim = victim
                               && (victim->m_nType == ENTITY_TYPE_PED
                                   || victim->m_nType == ENTITY_TYPE_VEHICLE);

            if (validVictim)
                StartFireAt (owner, victim);
            else
                StartFireAt (owner, point);
        }

        cb ();
    }

    static void
    Hooked_CWeapon_GenerateDamageEvent (auto &&cb, CPed *victim, CPed *creator,
                                        eWeaponType weaponType,
                                        int damageFactor, int pedPiece,
                                        char direction)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPONTYPE_SNIPERRIFLE)
        {
            StartFireAt (creator, victim);
        }

        cb ();
    }

    static void
    Hooked_CVehicle_InflictDamage (auto &&cb, CVehicle *thisVehicle,
                                   CPed *creator, eWeaponType weaponType,
                                   float damage, CVector coords)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPONTYPE_SNIPERRIFLE)
        {
            StartFireAt (creator, thisVehicle);
        }

        cb ();
    }

    static void
    Hooked_CObject_ObjectDamage (auto &&cb, CObject *thisObject, float damage,
                                 RwV3d *fxOrigin, RwV3d *fxDirection,
                                 CEntity *creator, eWeaponType weaponType)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPONTYPE_SNIPERRIFLE)
        {
            StartFireAt (creator, thisObject->GetPosition ());
        }

        cb ();
    }

    static void
    Hooked_Fx_c_AddBulletImpact (auto &&cb, RwV3d *position, RwV3d *direction,
                                 int surfnum, signed int count, float scale)
    {
        StartFireAt (FindPlayerPed (),
                     CVector (position->x, position->y, position->z));

        cb ();
    }
};

DEFINE_EFFECT (FireBulletsEffect, "effect_fire_bullets", 0);