#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"

#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class PedsExplodeWhenRunOverEffect : public EffectBase
{
    static inline bool hasRunOverPed = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        hasRunOverPed = false;

        for (int address : {0x54C5CC, 0x54C642, 0x60461F, 0x60491B, 0x604A0D})
        {
            injector::MakeCALL (address, Hooked_CPed_KillPedWithCar);
        }

        injector::MakeCALL (0x7374DA, Hooked_CWorld_TriggerExplosion);
        injector::MakeCALL (0x568271, Hooked_DamageAffectsPed);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    static void __fastcall Hooked_CPed_KillPedWithCar (CPed *thisPed, void *edx,
                                                       CVehicle *car,
                                                       float arg1, bool arg2)
    {
        hasRunOverPed = true;

        CVector pos = thisPed->GetPosition ();
        Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (pos.x, pos.y, pos.z,
                                                         7);

        thisPed->KillPedWithCar (car, arg1, arg2);
    }

    static void
    Hooked_CWorld_TriggerExplosion (CVector *point, float radius,
                                    float visibleDistance, CEntity *victim,
                                    CEntity *creator, bool a7, float damage)
    {
        if (hasRunOverPed) damage = 0.0f;

        CWorld::TriggerExplosion (*point, radius, visibleDistance, victim,
                                  creator, a7, damage);

        hasRunOverPed = false;
    }

    static bool __fastcall Hooked_DamageAffectsPed (CEventDamage *thisDamage,
                                                    void *edx, CPed *ped)
    {
        return !hasRunOverPed;
    }
};

DEFINE_EFFECT (PedsExplodeWhenRunOverEffect,
               "effect_peds_explode_when_run_over", 0);