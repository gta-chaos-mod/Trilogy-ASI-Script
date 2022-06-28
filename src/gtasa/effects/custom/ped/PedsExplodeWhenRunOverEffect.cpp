#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

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

        // TODO: Double check if these functions are hooked properly
        HOOK_METHOD_ARGS (inst, Hooked_CPed_KillPedWithCar,
                          void (CPed *, CVehicle *, float, bool), 0x54C5CC,
                          0x54C642, 0x60461F, 0x60491B, 0x604A0D);

        HOOK_ARGS (inst, Hooked_CWorld_TriggerExplosion,
                   void (CVector *, float, float, CEntity *, CEntity *, bool,
                         float),
                   0x7374DA);

        HOOK_METHOD (inst, Hooked_CEventDamage_AffectsPed,
                     bool (CEventDamage *, CPed *), 0x568271);
    }

    static void
    Hooked_CPed_KillPedWithCar (auto &&cb, CPed *thisPed, CVehicle *car,
                                float arg1, bool arg2)
    {
        hasRunOverPed = true;

        CVector pos = thisPed->GetPosition ();
        Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (pos.x, pos.y, pos.z,
                                                         7);

        cb ();
    }

    static void
    Hooked_CWorld_TriggerExplosion (auto &&cb, CVector *point, float radius,
                                    float visibleDistance, CEntity *victim,
                                    CEntity *creator, bool a7, float &damage)
    {
        if (hasRunOverPed) damage = 0.0f;

        cb ();

        hasRunOverPed = false;
    }

    static bool
    Hooked_CEventDamage_AffectsPed (auto &&cb)
    {
        return !hasRunOverPed || cb ();
    }
};

DEFINE_EFFECT (PedsExplodeWhenRunOverEffect,
               "effect_peds_explode_when_run_over", 0);