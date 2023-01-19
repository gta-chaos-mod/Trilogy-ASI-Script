#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class PedsCanExplodeOnDeathEffect : public EffectBase
{
    static inline unsigned int randomValue;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        // CPedDamageResponseCalculator::ComputeWillKillPed
        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *, void *,
                                char),
                          0x4B5B27);

        randomValue = inst->Random (0, 100000);
    }

    static void
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, void *a3, char a4)
    {
        cb ();

        if (!ped) return;

        if ((randomValue % 3 == 0) && ped->m_fHealth <= 0.0f)
        {
            auto p = ped->GetPosition ();
            Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (p.x, p.y, p.z, 11);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        randomValue = inst->Random (0, 100000);
    }
};

DEFINE_EFFECT (PedsCanExplodeOnDeathEffect, "effect_peds_can_explode_on_death",
               0);