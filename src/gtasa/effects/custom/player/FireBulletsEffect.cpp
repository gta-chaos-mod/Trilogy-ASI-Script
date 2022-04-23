#include "util/EffectBase.h"

#include <CFireManager.h>

using namespace plugin;

// TODO: Add support for snipers
class FireBulletsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int address : {0x73CD92, 0x741199, 0x7411DF, 0x7412DF, 0x741E30})
        {
            injector::MakeCALL (address, Hooked_CWeapon_DoBulletImpact);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (int address : {0x73CD92, 0x741199, 0x7411DF, 0x7412DF, 0x741E30})
        {
            injector::MakeCALL (address, 0x73B550);
        }
    }

    static void __fastcall Hooked_CWeapon_DoBulletImpact (
        CWeapon *weapon, void *edx, CEntity *owner, CEntity *victim,
        CVector *startPoint, CVector *endPoint, CColPoint *colPoint, int a7)
    {
        if (owner == FindPlayerPed ())
        {
            CVector point = colPoint->m_vecPoint;

            bool validVictim
                = victim
                  && (victim->m_nType == eEntityType::ENTITY_TYPE_PED
                      || victim->m_nType == eEntityType::ENTITY_TYPE_VEHICLE);

            if (validVictim)
                gFireManager.StartFire (victim, owner, 1.0f, 0, 2000, 0);
            else
                gFireManager.StartFire (point, 1.0f, 0, owner, 2000, 0, 1);
        }

        CallMethod<0x73B550, CWeapon *> (weapon, owner, victim, startPoint,
                                         endPoint, colPoint, a7);
    }
};

DEFINE_EFFECT (FireBulletsEffect, "effect_fire_bullets", 0);