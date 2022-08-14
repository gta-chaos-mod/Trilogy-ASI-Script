#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

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

        HOOK_STD_ARGS (inst, Hooked_Fx_c_AddBulletImpact,
                       void (RwV3d *, RwV3d *, int, signed int, float),
                       0x736545);

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CStreaming::RequestModel (MODEL_TEC9, 2); // Tec-9
        CStreaming::LoadAllRequestedModels (false);

        player->ClearWeapon (WEAPON_TEC9);
        player->ClearWeapon (WEAPON_MICRO_UZI);
        player->ClearWeapon (WEAPON_MP5);

        player->GiveWeapon (WEAPON_TEC9, 99999, 1);
        player->SetCurrentWeapon (player->GetWeaponSlot (WEAPON_TEC9));

        CStreaming::SetModelIsDeletable (MODEL_TEC9);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (!player->DoWeHaveWeaponAvailable (WEAPON_TEC9)) return;

        CWeapon weapon
            = player->m_aWeapons[player->GetWeaponSlot (WEAPON_TEC9)];
        if (weapon.m_nTotalAmmo > 500) player->SetAmmo (WEAPON_TEC9, 500);
    }

    static void
    TeleportToPosition (CPed *owner, CVector position)
    {
        owner->SetPosn (position);

        owner->PositionAnyPedOutOfCollision ();
    }

    // Can still sometimes teleport to the 0,0,0 point
    static bool
    IsPointValid (CVector v)
    {
        // Extra checks thanks to Zolika
        if (abs (v.x) > 1000000) return false;
        if (abs (v.y) > 1000000) return false;
        if (abs (v.z) > 1000000) return false;
        if (v.x == NAN) return false;
        if (v.y == NAN) return false;
        if (v.z == NAN) return false;
        if (v.x == INFINITY) return false;
        if (v.y == INFINITY) return false;
        if (v.z == INFINITY) return false;
        if (v.x == 0) return false;
        if (v.y == 0) return false;
        if (v.z == 0) return false;

        CVector playerPosition = FindPlayerPed ()->GetPosition ();

        float distance = DistanceBetweenPoints (v, playerPosition);
        return distance < 100.0f && distance > 0.01f;
    }

    static void
    Hooked_CWeapon_DoBulletImpact (auto &&cb, CWeapon *weapon, CEntity *owner,
                                   CEntity *victim, CVector *startPoint,
                                   CVector *endPoint, CColPoint *colPoint,
                                   int a7)
    {
        cb ();

        CVector point = colPoint->m_vecPoint;
        point.z += 1.0f;

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
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE
            && IsPointValid (victim->GetPosition ()))
            TeleportToPosition ((CPed *) creator, victim->GetPosition ());

        cb ();
    }

    static void
    Hooked_CVehicle_InflictDamage (auto &&cb, CVehicle *thisVehicle,
                                   CPed *creator, eWeaponType weaponType,
                                   float damage, CVector coords)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE
            && IsPointValid (thisVehicle->GetPosition ()))
            TeleportToPosition ((CPed *) creator, thisVehicle->GetPosition ());

        cb ();
    }

    static void
    Hooked_CObject_ObjectDamage (auto &&cb, CObject *thisObject, float damage,
                                 RwV3d *fxOrigin, RwV3d *fxDirection,
                                 CEntity *creator, eWeaponType weaponType)
    {
        if (creator == FindPlayerPed () && weaponType == WEAPON_SNIPERRIFLE
            && IsPointValid (thisObject->GetPosition ()))
            TeleportToPosition ((CPed *) creator, thisObject->GetPosition ());

        cb ();
    }

    static void
    Hooked_Fx_c_AddBulletImpact (auto &&cb, RwV3d *position, RwV3d *direction,
                                 int surfnum, signed int count, float scale)
    {
        CVector point = CVector (position->x, position->y, position->z);

        if (IsPointValid (point)) TeleportToPosition (FindPlayerPed (), point);

        cb ();
    }
};

DEFINE_EFFECT (PortalGunsEffect, "effect_portal_guns", 0);