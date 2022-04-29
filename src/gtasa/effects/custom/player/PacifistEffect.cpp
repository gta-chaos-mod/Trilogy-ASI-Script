#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"

#include <CCheat.h>

using namespace plugin;

// TODO: Add support for snipers
class PacifistEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x4B5B27, Hooked_CDamageCalculator_WillKillPed);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::MakeCALL (0x4B5B27, 0x4B3210);
    }

    static void __fastcall Hooked_CDamageCalculator_WillKillPed (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped, void *a3,
        char a4)
    {
        CallMethod<0x4B3210, CPedDamageResponseCalculator *> (thisCalc, ped, a3,
                                                              a4);

        if (!ped || !thisCalc || !thisCalc->m_pDamager) return;

        if (ped->m_fHealth <= 0.0f
            && (thisCalc->m_pDamager == FindPlayerPed ()
                || thisCalc->m_pDamager == FindPlayerVehicle (-1, false)))
        {
            CCheat::SuicideCheat ();
        }
    }
};

DEFINE_EFFECT (PacifistEffect, "effect_pacifist", GROUP_HEALTH);