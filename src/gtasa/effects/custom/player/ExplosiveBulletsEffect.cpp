#include <util/EffectBase.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

// TODO: Add support for snipers
class ExplosiveBulletsEffect : public EffectBase
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

            Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (point.x, point.y,
                                                             point.z, 0);
        }

        CallMethod<0x73B550, CWeapon *> (weapon, owner, victim, startPoint,
                                         endPoint, colPoint, a7);
    }
};

DEFINE_EFFECT (ExplosiveBulletsEffect, "effect_explosive_bullets", 0);