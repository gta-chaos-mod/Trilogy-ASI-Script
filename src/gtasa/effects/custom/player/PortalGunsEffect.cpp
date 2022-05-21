#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

// TODO: Snipers don't teleport when not hitting a ped, car or object
class PortalGunsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CWeapon_DoBulletImpact,
                          void (CWeapon *, CEntity *, CEntity *, CVector *,
                                CVector *, CColPoint *, int),
                          0x741199, 0x7411DF, 0x7412DF, 0x741E30);

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
    }

    static void
    TeleportToPosition (CPed *owner, CVector position)
    {
        owner->SetPosn (position);
        owner->PositionAnyPedOutOfCollision ();
    }

    static bool
    IsPointValid (CVector v)
    {
        return !(v.x < 5.0f && v.x > -5.0f && v.y < 5.0f && v.y > 5.0f
                 && v.z < 5.0f && v.z > 5.0f);
    }

    static void
    Hooked_CWeapon_DoBulletImpact (auto &&cb, CWeapon *weapon, CEntity *owner,
                                   CEntity *victim, CVector *startPoint,
                                   CVector *endPoint, CColPoint *colPoint,
                                   int a7)
    {
        cb ();

        CVector point = colPoint->m_vecPoint;
        if (owner == FindPlayerPed () && IsPointValid (point))
        {
            TeleportToPosition ((CPed *) owner, point);
        }
    }

    static void
    Hooked_CWeapon_GenerateDamageEvent (auto &&cb, CPed *victim, CPed *creator,
                                        eWeaponType weaponType,
                                        int damageFactor, int pedPiece,
                                        char direction)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE)
            TeleportToPosition ((CPed *) creator, victim->GetPosition ());

        cb ();
    }

    static void
    Hooked_CVehicle_InflictDamage (auto &&cb, CVehicle *thisVehicle,
                                   CPed *creator, eWeaponType weaponType,
                                   float damage, CVector coords)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE)
            TeleportToPosition ((CPed *) creator, thisVehicle->GetPosition ());

        cb ();
    }

    static void
    Hooked_CObject_ObjectDamage (auto &&cb, CObject *thisObject, float damage,
                                 RwV3d *fxOrigin, RwV3d *fxDirection,
                                 CEntity *creator, eWeaponType weaponType)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE)
            TeleportToPosition ((CPed *) creator, thisObject->GetPosition ());

        cb ();
    }
};

DEFINE_EFFECT (PortalGunsEffect, "effect_portal_guns", 0);