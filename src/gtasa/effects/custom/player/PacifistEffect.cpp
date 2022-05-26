#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CCheat.h>

class PacifistEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CPedDamageResponseCalculator_WillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *, void *,
                                char),
                          0x4B5B27);
    }

    static void
    Hooked_CPedDamageResponseCalculator_WillKillPed (
        auto &&cb, CPedDamageResponseCalculator *thisCalc, CPed *ped, void *a3,
        char a4)
    {
        cb ();

        if (!ped || !thisCalc || !thisCalc->m_pDamager) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (ped->m_fHealth <= 0.0f
            && (thisCalc->m_pDamager == player
                || thisCalc->m_pDamager == FindPlayerVehicle (-1, false)))
        {
            CCheat::SuicideCheat ();
        }
    }
};

DEFINE_EFFECT (PacifistEffect, "effect_pacifist", GROUP_HEALTH);