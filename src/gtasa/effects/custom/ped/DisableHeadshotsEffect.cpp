#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class DisableHeadshotsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {

        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *,
                                uint8_t *, char),
                          0x4B5B27);
    }

    static void
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, uint8_t *cDamageResponseInfo, char a4)
    {
        if (thisCalc->m_pedPieceType == 9)
            thisCalc->m_pedPieceType = (ePedPieceTypes) 8;

        cb ();
    }
};

// clang-format off
DEFINE_EFFECT (DisableHeadshotsEffect, "effect_disable_headshots", GROUP_HEALTH);
// clang-format on